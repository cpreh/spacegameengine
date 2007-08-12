// C
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>
// C++
#include <iostream>
#include <map>
#include <boost/shared_array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>
// sge
#include "../../src/math/matrix.hpp"
#include "../../src/plugin_manager.hpp"
#include "../../src/plugin.hpp"
#include "../../src/renderer/renderer.hpp"
#include "../../src/renderer/renderer_system.hpp"
#include "../../src/input/input_system.hpp"
#include "../../src/input/key_state_tracker.hpp"
#include "../../src/timer.hpp"
#include "../../src/image/image_loader.hpp"
#include "../../src/image/image.hpp"
#include "../../src/renderer/color.hpp"
#include "../../src/renderer/lock_ptr.hpp"
#include "../../src/math/constants.hpp"
#include "../../src/math/rect.hpp"
#include "../../src/media.hpp"
#include "../../src/accessor.hpp"
#include "../../src/math/utility.hpp"
#include "../quadtree/quadtree.hpp"
#include "field.hpp"
#include "interpolation.hpp"
#include "noise_generation.hpp"
#include "noise_field_generator.hpp"
#include "island_extractor.hpp"

typedef field<sge::space_unit> heightmap;

void write_image(const sge::image_loader_ptr &image_loader,const heightmap &image,const std::string &fn)
{
	boost::scoped_array<sge::color> color_image(new sge::color[image.field_count()]);
	for (heightmap::const_iterator i = image.begin(); i != image.end(); ++i)
	{
		sge::color_element c = sge::color_element(*i * sge::color_to_color4_factor);
		color_image[i - image.begin()] = sge::make_color(c,c,c,1);
	}
	image_loader->create_image(color_image.get(),image.width(),image.height())->save(fn);
}

struct island_generator
{
	typedef float                                   float_type;
	typedef boost::uint8_t                          byte_type;
	typedef stdlib_noise_generation<float_type,int> noise_generator_type;
	typedef linear_interpolation<float_type>        interpolation_type;
	typedef noise_field_generator<float_type,linear_interpolation,stdlib_noise_generation> field_generator_type;

	enum stage_enum 
	{ 
		stage_none = 0,
		stage_noise_generated,
		stage_cloud_filtered,
		stage_extracted_island,
		stage_noised_island
	};

	stage_enum                     current_stage;

	// Noisefield Zeugs
	unsigned                         noise_field_octaves,noise_field_frequency;
	float_type                       noise_field_persistence;
	field_generator_type::field_type noise_field;

	// Cloudfilterzeugs
	heightmap                        cloudy_image;
	byte_type                        cloud_cover;
	float_type                       cloud_sharpness;
	
	// Inselextraktionszeug
	island_extractor::dim_type       desired_dim;
	heightmap                        selected_island;

	island_generator() 
		: current_stage(stage_none),
		  noise_field_octaves(6),noise_field_frequency(8),noise_field_persistence(float_type(0.5)),
			noise_field(256,256),
		  cloud_cover(190),cloud_sharpness(float_type(0.5)),
			desired_dim(64,64) {}

	void generate_noise_field()
	{
		field_generator_type generator;
		generator.generate(noise_field_octaves,noise_field_frequency,noise_field_persistence,noise_field);
		current_stage = stage_noise_generated;
	}

	struct cloud_filter_functor : public std::unary_function<float_type,float_type>
	{
		const byte_type      cover;
		const float_type     sharpness;
		const byte_type      max_byte;

		cloud_filter_functor(const byte_type cover,const float_type sharpness) 
			: cover(cover),sharpness(sharpness),max_byte(std::numeric_limits<byte_type>::max()) {}
		
		float_type operator()(const float_type &f)
		{
			// Fliesskommawert in Byte umwandeln
			byte_type a = byte_type(f * max_byte);
			
			// Erste Filterstufe
			byte_type b = byte_type(std::max(int(0),int(a) - int(cover)));
			
			// Zweite Filterstufe
			byte_type c = max_byte - byte_type(std::pow(sharpness,float_type(b)) * float_type(max_byte));

			// Und wieder in float
			return float_type(c) / float_type(max_byte);
		}
	};

	void apply_cloud_filter()
	{
		if (current_stage < stage_noise_generated)
			throw sge::exception("tried to apply cloud filter before noise was generated");

		cloudy_image = heightmap(noise_field.dim());
		std::transform(noise_field.begin(),noise_field.end(),cloudy_image.begin(),cloud_filter_functor(cloud_cover,cloud_sharpness));
		current_stage = stage_cloud_filtered;
	}

	void extract_island()
	{
		if (current_stage < stage_cloud_filtered)
			throw sge::exception("tried to extract island without cloud filtering first");

		if (current_stage >= stage_extracted_island)
			throw sge::exception("already extracted an island");

		island_extractor::field_list_type islands;
		island_extractor extractor(cloudy_image);
		extractor.extract_list(islands);

		island_extractor::field_list_type::const_iterator nearest = islands.begin();
		for (island_extractor::field_list_type::const_iterator i = islands.begin(); i != islands.end(); ++i)
		{
			if (sge::math::unsigned_diff(i->width(),desired_dim.w()) < sge::math::unsigned_diff(nearest->width(),desired_dim.w()))
				nearest = i;
			if (sge::math::unsigned_diff(i->height(),desired_dim.h()) < sge::math::unsigned_diff(nearest->height(),desired_dim.h()))
				nearest = i;
		}

		selected_island = *nearest;
		selected_island.add_border(2);
		current_stage = stage_extracted_island;

	}

	void blur_island()
	{
		selected_island.blur();
	}

	void autogen()
	{
		island_extractor::dim_type resulting_dim;
		unsigned counter = 0;
		while (sge::math::unsigned_diff(resulting_dim.w(),desired_dim.w()) > 10 && sge::math::unsigned_diff(resulting_dim.h(),desired_dim.h()) > 10)
		{
			current_stage = stage_none;
			generate_noise_field();
			apply_cloud_filter();
			extract_island();
			resulting_dim = selected_island.dim();
		}
		blur_island();
	}

	const heightmap selected() const
	{
		return selected_island;
	}
};

void generate_heightmap_particles(heightmap &map)
{
	map.zero();

	// Zufallsfeld auswaehlen
	sge::math::vector<unsigned,2> current_field(rand()%map.width(),rand()%map.height());

	const unsigned iterations = 10000;
	for (unsigned i = 0; i < iterations; ++i)
	{
		map.pos(current_field) += 0.05;

		if (current_field.x() == 0)
			current_field.x()++;
		if (current_field.x() == map.width() - 1)
			current_field.x()--;
		if (current_field.y() == 0)
			current_field.y()++;
		if (current_field.y() == map.height() - 1)
			current_field.y()--;

		unsigned r = rand() % 4;
		if (r == 0)
			current_field.x()++;
		else if (r == 1)
			current_field.x()--;
		else if (r == 2)
			current_field.y()++;
		else
			current_field.y()--;
	}

	map.blur();
}

struct binary_combinator : public std::binary_function<heightmap::value_type,heightmap::value_type,heightmap::value_type>
{
	heightmap::value_type operator()(const heightmap::value_type &t, const heightmap::value_type &b) const
	{
		return sge::math::almost_zero(b) ? heightmap::value_type(0) : t;
	}
};

void combine_binary(heightmap &target,const heightmap &binary)
{
	assert(target.dim() == binary.dim());
	std::transform(target.begin(),target.end(),binary.begin(),target.begin(),binary_combinator());
}

void generate_heightmap_hills(heightmap &map,const heightmap &binary_map)
{
	map.zero();

	const unsigned iterations = 800;
	heightmap::value_type max_height = 0,min_height = std::numeric_limits<heightmap::value_type>::max();
	for (unsigned i = 0; i < iterations; ++i)
	{
		const heightmap::value_type radius = (rand() / (RAND_MAX + 1.0)) * heightmap::value_type(8);
		//const heightmap::value_type theta = (rand() / (RAND_MAX+1.0))*2*sge::math::PI;
		//const heightmap::value_type distance = (rand() / (RAND_MAX+1.0))*map.width()/2;

		// Zufallsfeld auswaehlen
		//const sge::math::vector<unsigned,2> current_field(/*rand()%map.width(),rand()%map.height()*/map.width()/2+std::cos(theta)*distance,map.width()/2+std::sin(theta)*distance);
		const sge::math::vector<unsigned,2> current_field(rand()%map.width(),rand()%map.height());


		// TODO: Das hier schneller machen, indem man nur die naehere Umgebung des Zufallpunkts durchgeht
		for (unsigned x = 0; x < map.width(); ++x)
		{
			for (unsigned y = 0; y < map.height(); ++y)
			{
				const heightmap::value_type x_diff = x-heightmap::value_type(current_field.x());
				const heightmap::value_type y_diff = y-heightmap::value_type(current_field.y());
				const heightmap::value_type value = radius*radius - ((x_diff*x_diff)+(y_diff*y_diff));

				if (value < 0)
					continue;

				map.pos(x,y) += value;
				max_height = std::max(max_height,map.pos(x,y));
				min_height = std::min(min_height,map.pos(x,y));
			}
		}
	}

	combine_binary(map,binary_map);

	for (heightmap::iterator i = map.begin(); i != map.end(); ++i)
	{
		*i = (*i-min_height)/(max_height-min_height);
		*i *= *i;
	}

	map.blur();
}

int main()
{
	std::srand(std::time(0));

	sge::plugin_manager pm;
	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());

	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	sge::key_state_tracker ks(is);
	sge::timer frame_timer(1000);

	// Heigghtmap einlesen
	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());

	island_generator generator;
	generator.autogen();

	//color_image &extracted = generator.extracted_island;
	write_image(pl,generator.selected(),"form.bmp");
	
	heightmap m(generator.selected().dim());
	generate_heightmap_hills(m,generator.selected());

	write_image(pl,m,"feld.bmp");

	const sge::math::dim2 field_dim(2,2);
	const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex), m.width()*m.height());

	sge::quadtree tree(2);

	// Model daraus generieren
	float texture_granularity = 16;
	{
		heightmap::iterator pp = m.begin();
		sge::lock_ptr<sge::vertex_buffer_ptr> _lock(model_vb);
		sge::vertex_buffer::iterator vbit = model_vb->begin();
		// Fuer den Tree
		sge::quadtree::vertex_container_type &vertices = tree.vertices();
		for (sge::image::size_type y = 0; y < m.height(); ++y)
		{
			for (sge::image::size_type x = 0; x < m.width(); ++x)
			{
				sge::math::vector3 pos = sge::math::vector3(x * field_dim.w(),50*(*pp++),-y * field_dim.h());
				//sge::math::vector3 pos = sge::math::vector3(x * field_dim.w(),0,-y * field_dim.h());
				vertices.push_back(pos);
				vbit->pos() = pos;
				vbit->tex() = sge::math::vector2(sge::space_unit(x)/m.width()*texture_granularity,sge::space_unit(y)/m.height()*texture_granularity);
				vbit++;
			}
		}
	}

	// Fuer den Tree
	//std::vector<quadtree::indexed_triangle> triangles;
	{
		sge::quadtree::lock_ptr lock(tree);
		sge::quadtree::triangle_container_type &triangles = tree.triangles();
		for (sge::image::size_type y = 0; y < (m.height()-1); ++y)
		{
			for (sge::image::size_type x = 0; x < (m.width()-1); ++x)
			{
				sge::quadtree::indexed_triangle right;
				right.vertices[0] = y * m.width() + x;
				right.vertices[1] = y * m.width() + x + 1;
				right.vertices[2] = (y + 1) * m.width() + x + 1;
				sge::quadtree::indexed_triangle left;
				left.vertices[0] = y * m.width() + x;
				left.vertices[1] = (y + 1) * m.width() + x + 1;
				left.vertices[2] = (y + 1) * m.width() + x;
				triangles.push_back(right);
				triangles.push_back(left);
			}
		}
	}

	const sge::image_ptr grass_image = pl->load_image(sge::media_path() + "grass.png");

	const sge::texture_ptr textures[] = {
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::point_filter),
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::linear_filter),
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::mip_filter),
		rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::trilinear_filter)
	};

//	const sge::texture_ptr grass_texture = rend->create_texture(grass_image->data(), grass_image->width(), grass_image->height(), sge::linear_filter);

	bool running = true;

	unsigned selected_texture = 2;

	rend->set_texture(textures[selected_texture]);
	rend->set_bool_state(sge::bool_state::enable_zbuffer,true);
	rend->set_bool_state(sge::bool_state::clear_zbuffer,true);
	rend->set_bool_state(sge::bool_state::enable_culling,true);
	rend->set_bool_state(sge::bool_state::clear_backbuffer,true);
	rend->set_cull_mode(sge::cull_mode::back);
	rend->set_float_state(sge::float_state::zbuffer_clear_val,0);
	rend->set_depth_func(sge::depth_func::greater);

	sge::math::vector3 translation(-31.5,-3,-30);
	sge::space_unit fovy_deg = 90,fovy_rad = fovy_deg * sge::math::PI / 180,near = 1,far = 100,rot = 0;
	sge::space_unit aspect = static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height();

	sge::timer press_timer(500);
	while (running)
	{
		rend->begin_rendering();
		sge::window::dispatch();
		is->dispatch();

		translation.x() += ks[sge::KC_LEFT] * 0.01;
		translation.x() -= ks[sge::KC_RIGHT] * 0.01;
		translation.y() -= ks[sge::KC_UP] * 0.01;
		translation.y() += ks[sge::KC_DOWN] * 0.01;
		translation.z() += ks['w'] * 0.01;
		translation.z() -= ks['s'] * 0.01;

		if(ks['x'] && press_timer.update())
		{
			selected_texture = (selected_texture+1) % (sizeof(textures)/sizeof(sge::texture_ptr));
			rend->set_texture(textures[selected_texture]);
		}

	//	sge::space_unit aspect = static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height();
		// Alte Formel ohne 2* (anscheinend falsch)
		//sge::space_unit fovy_rad = fovy_deg*sge::math::PI/180,hnear = 2*std::tan(fovy_rad/2)*near,wnear = hnear * aspect,fovx_rad = 2*std::atan((wnear/2)/near);
		//sge::space_unit fovy_rad = fovy_deg*sge::math::PI/180,hnear = 2*std::tan(fovy_rad/2)*near,wnear = 2 * hnear * aspect,fovx_rad = 2*std::atan((wnear/2)/near);

		rend->transform(sge::math::matrix_translation(translation));
		// Projektionsmatrix setzen
		rend->projection(sge::math::matrix_perspective(aspect,fovy_rad,near,far));
	//	rend->projection(matrix_perspective(static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));
//		rend->projection(matrix_perspective(static_cast<sge::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));

	//	sge::math::space_matrix perspect = 
	//				sge::math::transpose(sge::math::matrix_perspective(static_cast../../src::space_unit>(rend->screen_width()) / rend->screen_height(),fovy_rad,near,far));

	//	sge::math::vector3 nl(perspect[0][3]+perspect[0][0],perspect[1][3]+perspect[1][0],perspect[2][3]+perspect[2][0]);
	//	std::cout << "left normal: " << nl.normalize() << "\n";

		sge::quadtree::index_container_type indices;
		tree.get_visible(sge::frustum_info(-translation,fovy_rad,rot,near,far,aspect),indices);
		if (indices.size() > 0)
		{
			const sge::index_buffer_ptr model_ib = rend->create_index_buffer(indices.size());
			{
				sge::lock_ptr<sge::index_buffer_ptr> _lock(model_ib);
				std::copy(indices.begin(),indices.end(),model_ib->begin());
			}
			rend->render(model_vb,model_ib,0,model_vb->size(),sge::indexed_primitive_type::triangle,indices.size()/3,0);
		}

		// Hier Programmlogik
		if (ks[sge::KC_ESC])
			running = false;

		rend->end_rendering();
	}
}

// C
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>
// C++
#include <iostream>
#include <boost/shared_array.hpp>
// sge
#include <sge/math/matrix.hpp>
#include <sge/plugin_manager.hpp>
#include <sge/plugin.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/renderer/renderer_system.hpp>
#include <sge/input/input_system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/timer.hpp>
#include <sge/image/image_loader.hpp>
#include <sge/image/image.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/lock_ptr.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/rect.hpp>
#include <sge/media.hpp>
#include <sge/accessor.hpp>
//#include "quadtree.hpp"

template<typename FLOAT>
struct linear_interpolation
{
	FLOAT operator()(const FLOAT a,const FLOAT b, const FLOAT x) const
	{
		return a*(FLOAT(1)-x)+x*b;
	}
};

template<typename FLOAT,typename COORD>
struct standard_noise_generation
{
	FLOAT abs(const FLOAT a) const
	{
		if (a == FLOAT(0)) 
			return a;
		return a > 0 ? a : -a;
	}

	FLOAT operator()(COORD x,COORD y) const 
	{
		COORD n = x + y * COORD(57); n = (n<<13) ^ n;
		return abs((FLOAT(1.0) - ((n * (n * n * COORD(15731) + COORD(789221)) + COORD(1376312589)) & COORD(0x7fffffff)) / FLOAT(1073741824.0)));
	}
};

template< typename FLOAT,template<typename> class interpolation, template<typename,typename> class noise_generation >
struct island_generator
{
	typedef FLOAT                                  value_type;
	typedef sge::math::dim<unsigned,2>             dim_type;
	typedef boost::shared_array<value_type>        array_type;
	typedef unsigned                               coord_type;

	const dim_type                           dim;
	const interpolation<value_type>          interpolator;
	const unsigned                           octaves;
	const value_type                         persistence;
	noise_generation<value_type,coord_type>  noise_generator;

	island_generator(const dim_type &dim,const unsigned octaves,const value_type persistence) 
			: dim(dim),interpolator(),octaves(octaves),persistence(persistence) {}
	dim_type::value_type height() const { return dim.h(); }
	dim_type::value_type width() const { return dim.w(); }

	value_type value(const coord_type x,const coord_type y)
	{
		unsigned freq = 2;
		value_type    amplitude = persistence;
		value_type    value;
		for (unsigned i = 0; i < octaves; ++i)
		{
			// Position im Raster, das durch die Frequenz aufgespannt wird
			const sge::math::vector<coord_type,2> ipos(x*freq/width(),y*freq/height());
			// Noise-Wert an der momentan und naechsten Rasterposition
			const value_type noise_cur = noise_generator(ipos.x(),ipos.y());
			const value_type noise_xn = noise_generator(ipos.x()+coord_type(1),ipos.y());
			const value_type noise_yn = noise_generator(ipos.x(),ipos.y()+coord_type(1));
			const value_type noise_xnyn = noise_generator(ipos.x()+coord_type(1),ipos.y()+coord_type(1));

			const value_type fractional_x = (x % (width()/freq)) / value_type(width()/freq);
			const value_type fractional_y = (y % (height()/freq)) / value_type(height()/freq);

			const value_type interpolated_x = interpolator(noise_cur,noise_xn,fractional_x);
			const value_type interpolated_xn = interpolator(noise_yn,noise_xnyn,fractional_x);

			value += interpolator(interpolated_x,interpolated_xn,fractional_y) * amplitude;

			// Werte updaten
			freq *= 2;
			amplitude *= persistence;
		}

		return std::min(value,value_type(1));
	}

	array_type generate()
	{
		// Erstmal Array neu setzen
		array_type array(new value_type[width()*height()]);

		// Jeden Pixel durchgehen und Oktaven addieren
		for (coord_type i = coord_type(0); i < width()*height(); ++i)
		{
			array[i] = value(i % width(),i / width());
		}

		return array;
	}
};

int main()
{
	sge::plugin_manager pm;
	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr image_loader(image_loader_plugin->get()());

	typedef island_generator<float,linear_interpolation,standard_noise_generation> generator_type;
	generator_type::dim_type dimension(256,256);
	generator_type generator(dimension,8,0.6f);
	generator_type::array_type array = generator.generate();

	boost::shared_array<sge::color> image(new sge::color[dimension.w()*dimension.h()]);
	for (unsigned i = 0; i < dimension.w()*dimension.h(); ++i)
	{
		sge::color_element n = static_cast<sge::color_element>(array[i] * std::numeric_limits<sge::color_element>::max());
		image[i] = sge::make_color(n,n,n,1);
	}

	image_loader->create_image(image.get(), dimension.w(), dimension.h())->save("test.bmp");

	#if 0
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
	

	const sge::math::dim2 field_dim(1,1);
	const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex), heightmap->height() * heightmap->width());

	sge::quadtree tree(2);

	// Model daraus generieren
	float texture_granularity = 4;
	{
		sge::image::const_pointer pp = heightmap->data();
		sge::lock_ptr<sge::vertex_buffer_ptr> _lock(model_vb);
		sge::vertex_buffer::iterator vbit = model_vb->begin();
		// Fuer den Tree
		sge::quadtree::vertex_container_type &vertices = tree.vertices();
		for (sge::image::size_type y = 0; y < heightmap->height(); ++y)
		{
			for (sge::image::size_type x = 0; x < heightmap->width(); ++x)
			{
				sge::math::vector3 pos = sge::math::vector3(x * field_dim.w(),30*sge::green_part_rgba_f(*pp++),-y * field_dim.h());
				//sge::math::vector3 pos = sge::math::vector3(x * field_dim.w(),0,-y * field_dim.h());
				vertices.push_back(pos);
				vbit->pos() = pos;
				vbit->tex() = sge::math::vector2(sge::space_unit(x)/heightmap->width()*texture_granularity,sge::space_unit(y)/heightmap->height()*texture_granularity);
				vbit++;
			}
		}
	}

	// Fuer den Tree
	//std::vector<quadtree::indexed_triangle> triangles;
	{
		sge::quadtree::lock_ptr lock(tree);
		sge::quadtree::triangle_container_type &triangles = tree.triangles();
		for (sge::image::size_type y = 0; y < (heightmap->height()-1); ++y)
		{
			for (sge::image::size_type x = 0; x < (heightmap->width()-1); ++x)
			{
				sge::quadtree::indexed_triangle right;
				right.vertices[0] = y * heightmap->width() + x;
				right.vertices[1] = y * heightmap->width() + x + 1;
				right.vertices[2] = (y + 1) * heightmap->width() + x + 1;
				sge::quadtree::indexed_triangle left;
				left.vertices[0] = y * heightmap->width() + x;
				left.vertices[1] = (y + 1) * heightmap->width() + x + 1;
				left.vertices[2] = (y + 1) * heightmap->width() + x;
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

	unsigned selected_texture = 0;

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
	#endif
}

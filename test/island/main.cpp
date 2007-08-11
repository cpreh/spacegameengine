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
#include <ctime>
#include <cstdlib>
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
	standard_noise_generation() {}
	standard_noise_generation(const COORD,const COORD) {}
	void reset() {};

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

template<typename FLOAT,typename COORD>
struct stdlib_noise_generation
{
	typedef std::vector<FLOAT> inner_type;
	typedef std::vector<inner_type> outer_type;
	outer_type pairs;

	stdlib_noise_generation() {}

	stdlib_noise_generation(const COORD w,const COORD h) 
	{ 
		reset(w,h);
	}

	void reset(const COORD w,const COORD h)
	{
		std::srand(std::time(0));

		pairs.resize(w+1);
		for (typename outer_type::iterator i = pairs.begin(); i != pairs.end(); ++i)
		{
			i->resize(h+1);
			std::fill(i->begin(),i->end(),FLOAT(-1));
		}
	}
	
	FLOAT operator()(const COORD x,const COORD y)
	{
		assert(x < pairs.size() || y < pairs[x].size());

		if (pairs[x][y] != FLOAT(-1))
			return pairs[x][y];

		return pairs[x][y] = FLOAT(std::rand() / (RAND_MAX + 1.0));
	}
};

template< typename FLOAT,template<typename> class interpolation, template<typename,typename> class noise_generation>
struct noise_field_generator
{
	typedef FLOAT                                  value_type;
	typedef sge::math::dim<unsigned,2>             dim_type;
	typedef boost::shared_array<value_type>        array_type;
	typedef unsigned                               coord_type;

	const interpolation<value_type>          interpolator;
	dim_type                                 dim;
	unsigned                                 octaves,frequency;
	value_type                               persistence;
	noise_generation<value_type,coord_type>  noise_generator;

	noise_field_generator()  : interpolator() {}
	dim_type::value_type height() const { return dim.h(); }
	dim_type::value_type width() const { return dim.w(); }

	value_type value(const coord_type x,const coord_type y)
	{
		unsigned freq = frequency;
		value_type    amplitude = persistence;
		value_type    value = value_type(0);

		dim_type ndim = dim;

		for (unsigned i = 0; i < octaves; ++i)
		{
			if (ndim.w()/freq == 0 || ndim.h()/freq == 0)
			{
				std::cerr << "Warning: frequency too high!\n";
				return value;
			}

			/*
			// Hoehe oder Breite nicht glatt durch die Frequenz teilbar?
			// Dann naechsthoehere Dimension suchen, ab der es teilbar ist
			if (ndim.w() % freq != 0)
				ndim.w() = ((width()/(width()/freq))+1)*(width()/freq);
			if (ndim.h() % freq != 0)
				ndim.h() = ((height()/(height()/freq))+1)*(height()/freq);
			*/

			// Position im Raster, das durch die Frequenz aufgespannt wird
			const sge::math::vector<coord_type,2> ipos(x*freq/ndim.w(),y*freq/ndim.h());
			// Noise-Wert an der momentan und naechsten Rasterposition
			const value_type noise_cur = noise_generator(ipos.x(),ipos.y());
			const value_type noise_xn = noise_generator(ipos.x()+coord_type(1),ipos.y());
			const value_type noise_yn = noise_generator(ipos.x(),ipos.y()+coord_type(1));
			const value_type noise_xnyn = noise_generator(ipos.x()+coord_type(1),ipos.y()+coord_type(1));

			const value_type fractional_x = (x % (ndim.w()/freq)) / value_type(ndim.w()/freq);
			const value_type fractional_y = (y % (ndim.h()/freq)) / value_type(ndim.h()/freq);

			const value_type interpolated_x = interpolator(noise_cur,noise_xn,fractional_x);
			const value_type interpolated_xn = interpolator(noise_yn,noise_xnyn,fractional_x);

			value += interpolator(interpolated_x,interpolated_xn,fractional_y) * amplitude;

			// Werte updaten
			freq *= 2;
			amplitude *= persistence;
		}

		return value;
	}

	array_type generate(const dim_type &_dim,const unsigned _octaves, const unsigned _frequency, const value_type _persistence)
	{
		dim = _dim;
		octaves = _octaves,frequency = _frequency;
		persistence = _persistence;

		noise_generator.reset(dim.w(),dim.h());

		// Erstmal Array neu setzen
		array_type array(new value_type[width()*height()]);

		// Maximalwert zum spaeteren Skalieren
		value_type max_value = 0;

		// Jeden Pixel durchgehen und Oktaven addieren
		for (coord_type i = coord_type(0); i < width()*height(); ++i)
		{
			array[i] = value(i % width(),i / width());
			max_value = std::max(array[i],max_value);
		}

		// Jeden Pixel nochmal durchgehen und anhand des Maximalwertes skalieren
		for (coord_type i = coord_type(0); i < width()*height(); ++i)
			array[i] /= max_value;

		return array;
	}
};

template<typename T>
T cloud_filter(const T n,const T cover,const T sharpness)
{
	T c = std::max(T(0),n - cover);
	return T(1)-std::pow(sharpness,c);
}

sge::color_element cloud_filter_color(const sge::color_element n, const sge::color_element cover, const float sharpness)
{
	sge::color_element c = sge::color_element(std::max(int(0),int(n) - cover));
	return std::numeric_limits<sge::color_element>::max() - sge::color_element(std::pow(sharpness,float(c)) * 255.0f);
}

template<typename T>
T abs(const T &t) { return t >= T(0) ? t : -t; }

struct color_image
{
	typedef sge::color                      color_type;
	typedef boost::shared_array<color_type> array_type;
	typedef sge::math::dim<int,2>           dim_type;

	array_type array;
	dim_type dim;

	color_type pixel(const int x,const int y) const { return array[y * dim.w() + x]; }
	dim_type::value_type pixel_count() const { return dim.w()*dim.h(); }
};

struct island_extractor
{
	typedef color_image                                      image_type;
	typedef color_image::dim_type                            dim_type;
	typedef sge::math::vector<dim_type::value_type,2>        pos_type;
	typedef sge::math::basic_rect<dim_type::value_type>      rect_type;
	typedef std::list<pos_type>                              pixel_list_type;
	typedef std::list<image_type>                            image_list_type;

	image_type image;

	island_extractor() {}
	island_extractor(image_type &image) { reset(image); }

	void reset(image_type &_image)
	{
		image = _image;

		// Randinseln fluten
		for (image_type::dim_type::value_type i = 0; i < image.dim.w(); ++i)
		{
			if (is_white(image.pixel(i,0)))
				fast_fill(pos_type(i,0));
			if (is_white(image.pixel(i,image.dim.h()-1)))
				fast_fill(pos_type(i,image.dim.h()-1));
		}

		for (image_type::dim_type::value_type i = 0; i < image.dim.h(); ++i)
		{
			if (is_white(image.pixel(0,i)))
				fast_fill(pos_type(0,i));
			if (is_white(image.pixel(image.dim.w()-1,i)))
				fast_fill(pos_type(image.dim.w()-1,i));
		}
	}

	template<typename T>
	bool almost_zero(const T t)
	{
		return t > T(-0.001) && t < T(0.001);
	}

	bool is_white(const image_type::color_type c)
	{
		return !almost_zero((sge::red_part_rgba_f(c) + sge::green_part_rgba_f(c) + sge::blue_part_rgba_f(c)) / 3);
	}

	void fast_fill(const pos_type &pos)
	{
		// Ungueltige Position?
		if (pos.x() < 0 || pos.y() < 0)
			return;
		
		if (pos.x() >= pos_type::value_type(image.dim.w()) || pos.y() >= pos_type::value_type(image.dim.h()))
			return;

		image_type::color_type *c = &image.array[image.dim.w() * pos.y() + pos.x()];

		if (!is_white(*c))
			return;

		*c = sge::make_color(0,0,0,1);

		fast_fill(pos_type(pos.x()-1,pos.y()-1));
		fast_fill(pos_type(pos.x(),pos.y()-1));
		fast_fill(pos_type(pos.x()+1,pos.y()-1));
		fast_fill(pos_type(pos.x()-1,pos.y()));
		fast_fill(pos_type(pos.x()+1,pos.y()));
		fast_fill(pos_type(pos.x()-1,pos.y()+1));
		fast_fill(pos_type(pos.x(),pos.y()+1));
		fast_fill(pos_type(pos.x()+1,pos.y()+1));
	}

	void flood_fill(pixel_list_type &pixel_list,const pos_type &pos,const unsigned recursion_depth)
	{
		// Ungueltige Position?
		if (pos.x() < 0 || pos.y() < 0)
			return;
		
		if (pos.x() >= pos_type::value_type(image.dim.w()) || pos.y() >= pos_type::value_type(image.dim.h()))
			return;

		image_type::color_type *c = &image.array[image.dim.w() * pos.y() + pos.x()];

		if (!is_white(*c))
			return;

		// Pixel hinzufuegen und auf 0 setzen.
		pixel_list.push_back(pos);
		*c = sge::make_color(0,0,0,1);

		flood_fill(pixel_list,pos_type(pos.x()-1,pos.y()-1),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x(),pos.y()-1),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x()+1,pos.y()-1),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x()-1,pos.y()),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x()+1,pos.y()),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x()-1,pos.y()+1),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x(),pos.y()+1),recursion_depth+1);
		flood_fill(pixel_list,pos_type(pos.x()+1,pos.y()+1),recursion_depth+1);
	}

	rect_type bounding_rect(const pixel_list_type &pixel_list)
	{
		rect_type b(pixel_list.front().x(),pixel_list.front().y(),pixel_list.front().x(),pixel_list.front().y());
		for (pixel_list_type::const_iterator i = pixel_list.begin(); i != pixel_list.end(); ++i)
		{
			if (i->x() < b.left)
				b.left = i->x();
			if (i->x() > b.right)
				b.right = i->x();
			if (i->y() < b.top)
				b.top = i->y();
			if (i->y() > b.bottom)
				b.bottom = i->y();
		}
		return rect_type(b.left,b.top,b.right+1,b.bottom+1);
	}

	void extract(image_list_type &images)
	{
		image_type n;
		while (extract(n))
			images.push_back(n);
	}

	bool extract(image_type &target)
	{
		pixel_list_type pixel_list;

		while (pixel_list.size() < pixel_list_type::size_type(50))
		{
			pixel_list.clear();

			// Ersten weissen Pixel suchen:
			for (image_type::dim_type::value_type i = 0; i < image.pixel_count(); ++i)
			{
				if (is_white(image.array[i]))
				{
					flood_fill(pixel_list,pos_type(i % image.dim.w(),i / image.dim.w()),0);
					break;
				}
			}

			if (pixel_list.size() == 0)
				break;
		}

		// Keine Insel (mehr) gefunden? :(
		if (pixel_list.size() == 0)
			return false;

		// Bounding-Rect bestimmen
		rect_type r = bounding_rect(pixel_list);

		pos_type lefttop = pos_type(r.left,r.top);
		target.dim = image_type::dim_type(r.width(),r.height());

		// Und in einzelnes Bild umwandeln
		target.array.reset(new image_type::color_type[(r.width())*(r.height())]);

		std::fill(target.array.get(),target.array.get() + r.width() * r.height(),0);

		// Koordinaten "normieren" und in Bild schreiben
		for (pixel_list_type::iterator i = pixel_list.begin(); i != pixel_list.end(); ++i)
		{
			*i -= lefttop;
			target.array[i->y() * r.width() + i->x()] = sge::colors::white;
		}
		return true;
	}
};

struct island_generator
{
	typedef float                                   float_type;
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
	field_generator_type::dim_type   noise_field_dim;
	unsigned                         noise_field_octaves,noise_field_frequency;
	float_type                       noise_field_persistence;
	field_generator_type::array_type noise_field_array;

	// Cloudfilterzeugs
	color_image                      cloudy_image;
	sge::color_element               cloud_cover;
	float_type                       cloud_sharpness;
	sge::color_element cloud_filter(const sge::color_element n)
	{
		sge::color_element c = sge::color_element(std::max(int(0),int(n) - cloud_cover));
		return std::numeric_limits<sge::color_element>::max() - sge::color_element(std::pow(cloud_sharpness,float_type(c)) * float_type(255.0f));
	}
	
	// Inselextraktionszeug
	island_extractor::dim_type       desired_dim;
	color_image                      extracted_island;

	island_generator() 
		: current_stage(stage_none),
		  noise_field_dim(256,256),noise_field_octaves(6),noise_field_frequency(8),noise_field_persistence(float_type(0.5)),
		  cloud_cover(190),cloud_sharpness(float_type(0.5)),
			desired_dim(64,64) {}

	void generate_noise_field()
	{
		field_generator_type generator;
		noise_field_array = generator.generate(noise_field_dim,noise_field_octaves,noise_field_frequency,noise_field_persistence);
		current_stage = stage_noise_generated;
	}

	void apply_cloud_filter()
	{
		if (current_stage < stage_noise_generated)
			throw sge::exception("tried to apply cloud filter before noise was generated");

		cloudy_image.dim = color_image::dim_type(noise_field_dim.w(),noise_field_dim.h());
		cloudy_image.array.reset(new color_image::color_type[cloudy_image.pixel_count()]);

		const sge::color_element max_color = std::numeric_limits<sge::color_element>::max();
		for (color_image::dim_type::value_type i = 0; i < cloudy_image.pixel_count(); ++i)
		{
			sge::color_element n = cloud_filter(static_cast<sge::color_element>(noise_field_array[i] * float_type(max_color)));
			cloudy_image.array[i] = sge::make_color(n,n,n,1);
		}

		current_stage = stage_cloud_filtered;
	}

	void extract_island()
	{
		if (current_stage < stage_cloud_filtered)
			throw sge::exception("tried to extract island without cloud filtering first");

		if (current_stage >= stage_extracted_island)
			throw sge::exception("already extracted an island");

		island_extractor::image_list_type islands;
		island_extractor extractor(cloudy_image);
		extractor.extract(islands);

		if (islands.size() == 0)
			throw sge::exception("no islands could be extracted!");

		const color_image *nearest = &islands.front();
		for (island_extractor::image_list_type::const_iterator i = islands.begin(); i != islands.end(); ++i)
		{
			if (abs(i->dim.w() - desired_dim.w()) < abs(nearest->dim.w() - desired_dim.w()))
				nearest = &(*i);
			if (abs(i->dim.h() - desired_dim.h()) < abs(nearest->dim.h() - desired_dim.h()))
				nearest = &(*i);
		}

		extracted_island = *nearest;
		current_stage = stage_extracted_island;
	}

	void noise_island()
	{
		if (current_stage != stage_extracted_island)
			throw sge::exception("invalid state to noise island");

		field_generator_type generator;
		// TODO: Sehr gehackt hier
		field_generator_type::array_type island_noise = generator.generate(field_generator_type::dim_type(noise_field_dim.w(),noise_field_dim.h()),8,2,0.7f);

		const sge::color_element max_color = std::numeric_limits<sge::color_element>::max();
		for (color_image::dim_type::value_type i = 0; i < extracted_island.pixel_count(); ++i)
		{
			const unsigned x = i % extracted_island.dim.w(),y = i / extracted_island.dim.h();
			sge::color4::value_type p = get_pixel(extracted_island,x,y);
			if (p != 0)
				std::cout << "pixel=" << p << "\n";
			sge::color_element n = static_cast<sge::color_element>(island_noise[y * noise_field_dim.w() + x] * float_type(p) * float_type(max_color));
			extracted_island.array[i] = sge::make_color(n,n,n,1);
	/*	if (extracted_island.array[i] == sge::colors::white)
			{
				const unsigned x = i % extracted_island.dim.w(),y = i / extracted_island.dim.h();
				sge::color_element n = static_cast<sge::color_element>(island_noise[y * noise_field_dim.w() + x] * float_type(max_color));
				extracted_island.array[i] = sge::make_color(n,n,n,1);
			}
	*/
		}

		current_stage = stage_noised_island;
	}

	sge::color4::value_type get_pixel(const color_image &image,const int x, const int y)
	{
		if (x < 0 || y < 0 || x >= image.dim.w() || y >= image.dim.h())
			return sge::color4::value_type(0);
		return sge::red_part_rgba_f(image.array[y * image.dim.w() + x]);
	}

	void blur_island()
	{
		for (color_image::dim_type::value_type i = 0; i < extracted_island.pixel_count(); ++i)
		{
			const int x = i % extracted_island.dim.w(),y = i / extracted_island.dim.w();
			
			sge::color4::value_type f = (
			                        get_pixel(extracted_island,x-1,y-1) + get_pixel(extracted_island,x,y-1) + get_pixel(extracted_island,x+1,y-1) +
			                        get_pixel(extracted_island,x-1,y) +   get_pixel(extracted_island,x,y) +   get_pixel(extracted_island,x+1,y) +
			                        get_pixel(extracted_island,x-1,y+1) + get_pixel(extracted_island,x,y+1) + get_pixel(extracted_island,x+1,y+1)
                              )/9.0;

			sge::color_element n = f * std::numeric_limits<sge::color_element>::max();
			extracted_island.array[i] = sge::make_color(n,n,n,1);
		}
	}

	void autogen()
	{
		island_extractor::dim_type resulting_dim;
		while (abs(resulting_dim.w() - desired_dim.w()) > 10 && abs(resulting_dim.h() - desired_dim.h()) > 10)
		{
			current_stage = stage_none;
			generate_noise_field();
			apply_cloud_filter();
			extract_island();
			resulting_dim = extracted_island.dim;
		}
		//blur_island();
		noise_island();
	}
};

void write_image(const sge::image_loader_ptr &image_loader,color_image image,const std::string &fn)
{
	image_loader->create_image(image.array.get(),image.dim.w(),image.dim.h())->save(fn);
}

int main()
{
	sge::plugin_manager pm;
	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr image_loader(image_loader_plugin->get()());

	island_generator generator;
	/*generator.generate_noise_field();
	generator.apply_cloud_filter();
	generator.extract_island();
	generator.noise_island();
	*/
	generator.autogen();
	image_loader->create_image(generator.extracted_island.array.get(), generator.extracted_island.dim.w(), generator.extracted_island.dim.h())->save("chosen.bmp");

	/*
	color_image image;
	image.dim = color_image::dim_type(generator.noise_field_dim.w(),generator.noise_field_dim.h());
	image.array.reset(new color_image::color_type[image.pixel_count()]);
	for (int i = 0; i < image.pixel_count(); ++i)
	{
		sge::color_element n = static_cast<sge::color_element>(generator.noise_field_array[i] * std::numeric_limits<sge::color_element>::max());
		image.array[i] = sge::make_color(n,n,n,1);
	}
	write_image(image_loader,image,"noise.bmp");
	*/
	/*
	std::cout << "Extracted island of size: " << generator.extracted_island.dim << "\n";
	write_image(image_loader,generator.extracted_island,"extracted.bmp");
	*/
	//image_loader->create_image(generator.cloudy_image.array.get(),generator.cloudy_image.dim.w(),generator.cloudy_image.dim.h())->save("chosen.bmp");
	/*

	typedef noise_field_generator<float,linear_interpolation,stdlib_noise_generation> generator_type;
	generator_type::dim_type dimension(256,256);
	generator_type generator;
	generator_type::array_type array = generator.generate(dimension,6,8,0.5f);

	boost::shared_array<sge::color> image(new sge::color[dimension.w()*dimension.h()]);
	for (unsigned i = 0; i < dimension.w()*dimension.h(); ++i)
	{
		sge::color_element n = static_cast<sge::color_element>(array[i] * std::numeric_limits<sge::color_element>::max());
		n = cloud_filter_color(n,sge::color_element(190),0.5f);
		image[i] = sge::make_color(n,n,n,1);
	}

	island_extractor extractor(image,island_extractor::dim_type(dimension.w(),dimension.h()));
	image_loader->create_image(image.get(), dimension.w(), dimension.h())->save("ursprung.bmp");

	//unsigned i = 0;
	//boost::ptr_list<island> islands;
	//islands.push_back(new island());
	
	std::list<island> islands;
	island n;
	while (extractor.extract(n))
		islands.push_back(n);
	
	island::dim_type desired_dim(64,64);
	const island *nearest = &islands.front();

	for (std::list<island>::const_iterator i = islands.begin(); i != islands.end(); ++i)
	{
		if (abs(i->dim.w() - desired_dim.w()) < abs(nearest->dim.w() - desired_dim.w()))
			nearest = &(*i);
		if (abs(i->dim.h() - desired_dim.h()) < abs(nearest->dim.h() - desired_dim.h()))
			nearest = &(*i);
	}

	std::cout << "Chosen dimension: " << nearest->dim << "\n";
	*/

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

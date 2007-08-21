#ifndef NOISE_FIELD_GENERATOR_HPP_INCLUDED
#define NOISE_FIELD_GENERATOR_HPP_INCLUDED

#include <iostream>
#include <algorithm>
#include "field.hpp"

template< typename FLOAT,template<typename> class interpolation, template<typename,typename> class noise_generation>
class noise_field_generator
{
	public:
	typedef FLOAT                                  value_type;
	typedef field<value_type>                      field_type;
	typedef typename field_type::dim_type          dim_type;
	typedef typename field_type::coord_type        coord_type;

	private:
	interpolation<value_type>                interpolator;
	noise_generation<value_type,coord_type>  noise_generator;
	unsigned                                 octaves,frequency;
	value_type                               persistence;
	dim_type                                 dim;

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
			const sge::math::basic_vector<coord_type,2> ipos(x*freq/ndim.w(),y*freq/ndim.h());
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

	public:
	noise_field_generator()  : interpolator() {}

	void generate(const unsigned _octaves, const unsigned _frequency, const value_type _persistence,field_type &array)
	{
		dim = array.dim();
		octaves = _octaves,frequency = _frequency;
		persistence = _persistence;

		noise_generator.reset(array.width(),array.height());

		// Maximalwert zum spaeteren Skalieren
		value_type max_value = 0;

		// Jeden Pixel durchgehen und Oktaven addieren
		for (coord_type x = 0; x < dim.w(); ++x)
		{
			for (coord_type y = 0; y < dim.h(); ++y)
			{
				array.pos(x,y) = value(x,y);
				max_value = std::max(array.pos(x,y),max_value);
			}
		}

		// Jeden Pixel nochmal durchgehen und anhand des Maximalwertes skalieren
		for (typename field_type::iterator i = array.begin(); i != array.end(); ++i)
			*i /= max_value;
	}
};

#endif

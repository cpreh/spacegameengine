/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <algorithm>
#include "../hsla.hpp"

namespace
{

sge::color_element hue_to_tridant(const sge::color_element n1, const sge::color_element n2, sge::color_element hue)
{
	const sge::color_element hsl_max = sge::hsla::hsl_max;

//	if(hue < 0) hue += hsl_max;
//	if(hue > hsl_max) hue -= hsl_max;

	if(hue < (hsl_max / 6))
		return (n1 + (((n2 - n1) * hue + (hsl_max / 12)) / (hsl_max / 6)));

	if(hue < (hsl_max / 2))
		return n2;

	if(hue < ((hsl_max * 2) / 3))
		return (n1 + (((n2 - n1) * (((hsl_max * 2) / 3) - hue) + (hsl_max / 12)) / (hsl_max / 6)));
	
	return n1;
}

}

sge::hsla::hsla(const color_element h, const color_element s, const color_element l, const color_element a)
 : _hue(h),
   _sat(s),
   _lum(l),
   _a(a)
{}

sge::hsla::hsla(const color c)
 : _a(color_alpha(c))
{
	init(color_red(c), color_green(c), color_blue(c));
}

void sge::hsla::init(const color_element r, const color_element g, const color_element b)
{
	const color_element color_max = std::max(std::max(r, g), b),
	                    color_min = std::min(std::min(r, g), b);

	_lum = (((color_max + color_min) * hsl_max) + rgb_max) / (2 * rgb_max);

	if(color_max == color_min) // achromatic case
	{
		_hue = hue_undefined;
		_sat = 0;
		return;
	}
	
	// chromatic case
	const color_element color_delta = color_max - color_min;

	_sat = (_lum <= (hsl_max / 2)) ? 
	       ((color_delta * hsl_max) + (color_delta / 2)) / (color_max + color_min) :
	       ((color_delta * hsl_max) + ((2 * rgb_max - color_delta) / 2)) / (2 * rgb_max - color_delta);

	const color_element temp_r = (((color_max - r) * (hsl_max /6)) + (color_delta /2)) / color_delta,
	                    temp_g = (((color_max - g) * (hsl_max /6)) + (color_delta /2)) / color_delta,
	                    temp_b = (((color_max - b) * (hsl_max /6)) + (color_delta /2)) / color_delta;

	if(r == color_max)
		_hue = temp_b - temp_g;
	else if(g == color_max)
		_hue = (hsl_max / 3) + temp_r - temp_b;
	else
		_hue = ((2 * hsl_max) / 3) + temp_g - temp_r;

	if(_hue < 0) _hue += hsl_max;
	if(_hue > hsl_max) _hue -= hsl_max;
}

sge::color sge::hsla::to_color() const
{
	if(sat() == 0) //achromatic case
	{
		const color_element e = (lum() * rgb_max) / hsl_max;
		return make_color(e,e,e,a());
	}
    
	// chromatic case
	const color_element temp2 = (lum() <= (hsl_max / 2)) ?
	                            (lum() * (hsl_max + sat()) + (hsl_max / 2)) / hsl_max :
	                             lum() + sat() - ((lum() * sat()) + (hsl_max / 2)) / hsl_max;

	const color_element temp1 = 2 * lum() - temp2;

	return make_color((hue_to_tridant(temp1, temp2, hue() + (hsl_max / 3)) * rgb_max + (hsl_max / 2)) / hsl_max,
	            (hue_to_tridant(temp1, temp2, hue())                 * rgb_max + (hsl_max / 2)) / hsl_max,
	            (hue_to_tridant(temp1, temp2, hue() - (hsl_max / 3)) * rgb_max + (hsl_max / 2)) / hsl_max,
	             a());
}

void sge::hsla::hue(const color_element e)
{
	_hue = e;
}

void sge::hsla::lum(const color_element e)
{
	_lum = e;
}

void sge::hsla::sat(const color_element e)
{
	_sat = e;
}

void sge::hsla::a(const color_element e)
{
	_a = e;
}

sge::color_element sge::hsla::hue() const
{
	return _hue;
}

sge::color_element sge::hsla::lum() const
{
	return _lum;
}

sge::color_element sge::hsla::sat() const
{
	return _sat;
}

sge::color_element sge::hsla::a() const
{
	return _a;
}


const sge::color_element sge::hsla::hsl_max;
const sge::color_element sge::hsla::rgb_max;
const sge::color_element sge::hsla::hue_undefined;

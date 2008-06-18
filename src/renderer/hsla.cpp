/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


/*#include <sge/renderer/hsla.hpp>
#include <algorithm>

namespace
{

sge::color_element hue_to_tridant(
	const sge::color_element n1,
	const sge::color_element n2,
	const sge::color_element hue)
{
	const sge::color_element hsl_max = sge::hsla::hsl_max;

	if(hue < (hsl_max / 6))
		return static_cast<sge::color_element>(n1 + (((n2 - n1) * hue + (hsl_max / 12)) / (hsl_max / 6)));

	if(hue < (hsl_max / 2))
		return static_cast<sge::color_element>(n2);

	if(hue < ((hsl_max * 2) / 3))
		return static_cast<sge::color_element>(n1 + (((n2 - n1) * (((hsl_max * 2) / 3) - hue) + (hsl_max / 12)) / (hsl_max / 6)));
	
	return n1;
}

}

sge::hsla::hsla(
	const color_element hue_,
	const color_element sat_,
	const color_element lum_,
	const color_element a_)
 : hue_(hue_),
   sat_(sat_),
   lum_(lum_),
   a_(a_)
{}

sge::hsla::hsla(const color c)
 : a_(color_alpha(c))
{
	init(color_red(c), color_green(c), color_blue(c));
}

void sge::hsla::init(
	const color_element r,
	const color_element g,
	const color_element b)
{
	const color_element color_max = std::max(std::max(r, g), b),
	                    color_min = std::min(std::min(r, g), b);

	lum_ = static_cast<color_element>((((color_max + color_min) * hsl_max) + rgb_max) / (2 * rgb_max));

	if(color_max == color_min) // achromatic case
	{
		hue_ = hue_undefined;
		sat_ = 0;
		return;
	}
	
	// chromatic case
	const color_element color_delta = static_cast<color_element>(color_max - color_min);

	sat_ = (lum() <= (hsl_max / 2)) 
	     ? static_cast<color_element>(((color_delta * hsl_max) + (color_delta / 2)) / (color_max + color_min))
	     :  static_cast<color_element>(((color_delta * hsl_max) + ((2 * rgb_max - color_delta) / 2)) / (2 * rgb_max - color_delta));

	const color_element temp_r = static_cast<color_element>((((color_max - r) * (hsl_max /6)) + (color_delta /2)) / color_delta),
	                    temp_g = static_cast<color_element>((((color_max - g) * (hsl_max /6)) + (color_delta /2)) / color_delta),
	                    temp_b = static_cast<color_element>((((color_max - b) * (hsl_max /6)) + (color_delta /2)) / color_delta);

	if(r == color_max)
		hue_ = static_cast<color_element>(temp_b - temp_g);
	else if(g == color_max)
		hue_ = static_cast<color_element>((hsl_max / 3) + temp_r - temp_b);
	else
		hue_ = static_cast<color_element>(((2 * hsl_max) / 3) + temp_g - temp_r);
}

sge::color sge::hsla::to_color() const
{
	if(sat() == 0) //achromatic case
	{
		const color_element e = static_cast<color_element>((lum() * rgb_max) / hsl_max);
		return make_color(e,e,e,a());
	}
    
	// chromatic case
	const color_element temp2 = (lum() <= (hsl_max / 2))
	                          ?  static_cast<color_element>((lum() * (hsl_max + sat()) + (hsl_max / 2)) / hsl_max)
	                          :  static_cast<color_element>(lum() + sat() - ((lum() * sat()) + (hsl_max / 2)) / hsl_max);

	const color_element temp1 = static_cast<color_element>(2 * lum() - temp2);

	return make_color(
		static_cast<color_element>((hue_to_tridant(temp1, temp2, static_cast<color_element>(hue() + (hsl_max / 3))) * rgb_max + (hsl_max / 2)) / hsl_max),
		static_cast<color_element>((hue_to_tridant(temp1, temp2, hue()) * rgb_max + (hsl_max / 2)) / hsl_max),
	        static_cast<color_element>((hue_to_tridant(temp1, temp2, static_cast<color_element>(hue() - (hsl_max / 3))) * rgb_max + (hsl_max / 2)) / hsl_max),
	        a());
}

void sge::hsla::hue(const color_element e)
{
	hue_ = e;
}

void sge::hsla::lum(const color_element e)
{
	lum_ = e;
}

void sge::hsla::sat(const color_element e)
{
	sat_ = e;
}

void sge::hsla::a(const color_element e)
{
	a_ = e;
}

sge::color_element sge::hsla::hue() const
{
	return hue_;
}

sge::color_element sge::hsla::lum() const
{
	return lum_;
}

sge::color_element sge::hsla::sat() const
{
	return sat_;
}

sge::color_element sge::hsla::a() const
{
	return a_;
}


const sge::color_element sge::hsla::hsl_max;
const sge::color_element sge::hsla::rgb_max;
const sge::color_element sge::hsla::hue_undefined;*/

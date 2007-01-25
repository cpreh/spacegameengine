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
#include "../color.hpp"

sge::color sge::rgba_to_hsla(const color_channel r, const color_channel g, const color_channel b, const color_channel a)
{
	const color_element color_max = std::max(std::max(r, g), b),
	                    color_min = std::min(std::min(r, g), b),
	                    lum = (((color_max + color_min) * hsl_max) + rgb_max) / (2 * rgb_max);

	if(color_max == color_min) // achromatic case
		return rgba(hue_undefined, 0, lum, a);
	
	// chromatic case
	color_element color_delta = color_max - color_min;

	const color_element sat = (lum <= (hsl_max / 2)) ? 
	                          ((color_delta * hsl_max) + (color_delta / 2)) / (color_max + color_min) :
	                          ((color_delta * hsl_max) + ((2 * rgb_max - color_delta) / 2)) / (2 * rgb_max - color_delta);

	const color_element temp_r = (((color_max - r) * (hsl_max /6)) + (color_delta /2)) / color_delta,
	                    temp_g = (((color_max - g) * (hsl_max /6)) + (color_delta /2)) / color_delta,
	                    temp_b = (((color_max - b) * (hsl_max /6)) + (color_delta /2)) / color_delta;

	color_element hue;
	if(r == color_max)
		hue = temp_b - temp_g;
	else if(g == color_max)
		hue = (hsl_max / 3) + temp_r - temp_b;
	else
		hue = ((2 * hsl_max) / 3) + temp_g - temp_r;

	if(hue < 0) hue += hsl_max;
	if(hue > hsl_max) hue -= hsl_max;

	return rgba(hue, sat, lum, a);
}

sge::color_element sge::hue_to_tridant(const color_element n1, const color_element n2, color_element hue)
{
	if(hue < 0) hue += hsl_max;
	if(hue > hsl_max) hue -= hsl_max;

	if(hue < (hsl_max / 6))
		return (n1 + (((n2 - n1) * hue + (hsl_max / 12)) / (hsl_max / 6)));

	if(hue < (hsl_max / 2))
		return n2;

	if(hue < ((hsl_max * 2) / 3))
		return (n1 + (((n2 - n1) * (((hsl_max * 2) / 3) - hue) + (hsl_max / 12)) / (hsl_max / 6)));
	
	return n1;
}

sge::color sge::hsla_to_color(const color_channel hue, const color_channel lum, const color_channel sat, const color_channel a)
{ 
	if(sat == 0) //achromatic case
	{
		const color_element e = (lum * rgb_max) / hsl_max;
		return rgba(e,e,e,a);
	}
    
	// chromatic case

	const color_element temp2 = (lum <= (hsl_max / 2)) ?
	                            (lum * (hsl_max + sat) + (hsl_max / 2)) / hsl_max :
	                            lum + sat - ((lum * sat) + (hsl_max / 2)) / hsl_max;

	const color_element temp1 = 2 * lum - temp2;

	return rgba((hue_to_tridant(temp1, temp2, (unsigned)(hue + (hsl_max / 3))) * rgb_max + (hsl_max / 2)) / hsl_max,
	            (hue_to_tridant(temp1, temp2, hue) * rgb_max + (hsl_max / 2)) / hsl_max,
	            (hue_to_tridant(temp1, temp2, (unsigned)(hue - (hsl_max / 3))) * rgb_max + (hsl_max / 2)) / hsl_max,
		    a);
}

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


#ifndef SGE_COLOR_HPP_INCLUDED
#define SGE_COLOR_HPP_INCLUDED

#include <ostream>

#include "../types.hpp"
#include "../typeswitch.hpp"

namespace sge
{

typedef uint32 color;

template<unsigned Depth> struct BitDepth;
template<> struct BitDepth<16> { typedef int16 color; };
template<> struct BitDepth<32> { typedef sge::color color; };
typedef BitDepth<16> BitDepth16;
typedef BitDepth<32> BitDepth32;

#define SGE_RGBA_MAKRO(r,g,b,a) color(color(r) << 24 | color(g) << 16 | color(b) << 8 | color(a))

template<unsigned char r, unsigned char g, unsigned char b, unsigned char a> struct static_rgba {
	static const color value = SGE_RGBA_MAKRO(r,g,b,a);
};

template<unsigned char r, unsigned char g, unsigned char b> struct static_rgb {
	static const color value = static_rgba<r,g,b,255>::value;
};

inline color rgba(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
	return SGE_RGBA_MAKRO(r,g,b,a);
}

#undef SGE_RGBA_MAKRO

inline float   red_part_rgba_f(const color c) { return ((c & 0xFF000000) >> 24) / 255.f; }
inline float green_part_rgba_f(const color c) { return ((c &   0xFF0000) >> 16) / 255.f; }
inline float  blue_part_rgba_f(const color c) { return ((c &     0xFF00) >>  8) / 255.f; }
inline float alpha_part_rgba_f(const color c) { return  (c &       0xFF)        / 255.f; }

namespace colors {
	const color black  = static_rgb<   0,   0,   0>::value,
	            white  = static_rgb< 255, 255, 255>::value,
	            red    = static_rgb< 255,   0,   0>::value,
	            green  = static_rgb<   0, 255,   0>::value,
	            blue   = static_rgb<   0,   0, 255>::value,
	            yellow = static_rgb< 255, 255,   0>::value,
	            purple = static_rgb<0xa0,0x20,0xf0>::value,
	            orange = static_rgb<0xff,0xa5,   0>::value,
	            transparent = static_rgba<0,0,0,0>::value;
}

struct color4 {
	typedef space_unit value_type;
	color4(const value_type r = 0, const value_type g = 0, const value_type b = 0, const value_type a = 0)
	: r(r), g(g), b(b), a(a) {}

	value_type r,g,b,a;
};

inline std::ostream& operator<< (std::ostream& os, const color4& col)
{
	return os << '(' << col.r << ',' << col.g << ',' << col.b << ',' << col.a << ')';
}

inline bool operator==(const color4& l, const color4& r)
{
	return l.a == r.a && l.r == r.r && l.g == r.g && l.b == r.b;
}

inline bool operator!=(const color4& l, const color4& r)
{
	return !(l==r);
}

inline color4 color_to_color4(const color c)
{
	return color4(red_part_rgba_f(c), green_part_rgba_f(c), blue_part_rgba_f(c), alpha_part_rgba_f(c));
}

inline color rgba_to_argb(const color c)
{
	return (c >> 8) | ((c & 0xFF) << 24);
}

inline color argb_to_rgba(const color c)
{
	return (c << 8) | ((c & 0xFF000000) >> 24);
}

inline color rgba_to_abgr(const color c)
{
	return ((c & 0xFF000000) >> 24) |
	       ((c & 0x00FF0000) >>  8) |
	       ((c & 0x0000FF00) <<  8) |
	       ((c & 0x000000FF) << 24);
}

inline color abgr_to_rgba(const color c)
{
	return rgba_to_abgr(c);
}

}

#endif

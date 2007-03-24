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
typedef uint8 color_channel;
typedef int16 color_element;

template<unsigned Depth> struct BitDepth;
template<> struct BitDepth<16> { typedef int16 color; };
template<> struct BitDepth<32> { typedef sge::color color; };
typedef BitDepth<16> BitDepth16;
typedef BitDepth<32> BitDepth32;

#define SGE_RGBA_MAKRO(r,g,b,a) color(color(r) << 24 | color(g) << 16 | color(b) << 8 | color(a))

template<color_element r, color_element g, color_element b, color_element a> struct static_rgba {
	static const color value = SGE_RGBA_MAKRO(r,g,b,a);
};

template<color_element r, color_element g, color_element b> struct static_rgb {
	static const color value = static_rgba<r,g,b,255>::value;
};

inline color rgba(const color_element r, const color_element g, const color_element b, const color_element a)
{
	return SGE_RGBA_MAKRO(r,g,b,a);
}

#undef SGE_RGBA_MAKRO

inline float   red_part_rgba_f(const color c) { return ((c & 0xFF000000) >> 24) / 255.f; }
inline float green_part_rgba_f(const color c) { return ((c &   0xFF0000) >> 16) / 255.f; }
inline float  blue_part_rgba_f(const color c) { return ((c &     0xFF00) >>  8) / 255.f; }
inline float alpha_part_rgba_f(const color c) { return  (c &       0xFF)        / 255.f; }

inline color_element   rgba_red(const color c) { return static_cast<color_element>((c & 0xFF000000) >> 24); }
inline color_element rgba_green(const color c) { return static_cast<color_element>((c &   0xFF0000) >> 16); }
inline color_element  rgba_blue(const color c) { return static_cast<color_element>((c &     0xFF00) >>  8); }
inline color_element rgba_alpha(const color c) { return static_cast<color_element> (c &       0xFF)       ; }

namespace colors {
	const color aliceblue           = static_rgb<240, 248, 255>::value,
	            antiquewhite        = static_rgb<250, 235, 215>::value,
	            aqua                = static_rgb<0  , 255, 255>::value,
	            aquamarine          = static_rgb<127, 255, 212>::value,
	            azure               = static_rgb<240, 255, 255>::value,
	            beige               = static_rgb<245, 245, 220>::value,
	            bisque              = static_rgb<255, 228, 196>::value,
	            black               = static_rgb<  0,   0,   0>::value,
	            blanchedalmond      = static_rgb<255, 235, 205>::value,
	            blue                = static_rgb<  0,   0, 255>::value,
	            blueviolet          = static_rgb<138,  43, 226>::value,
	            brown               = static_rgb<165,  42,  42>::value,
	            burlywood           = static_rgb<222, 184, 135>::value,
	            cadetblue           = static_rgb< 95, 158, 160>::value,
	            chartreuse          = static_rgb<127, 255,   0>::value,
	            chocolate           = static_rgb<210, 105,  30>::value,
	            coral               = static_rgb<255, 127,  80>::value,
	            cornflowerblue      = static_rgb<100, 149, 237>::value,
	            cornsilk            = static_rgb<255, 248, 220>::value,
	            crimson             = static_rgb<220,  20,  60>::value,
	            cyan                = static_rgb<  0, 255, 255>::value,
	            darkblue            = static_rgb<  0,   0, 139>::value,
	            darkcyan            = static_rgb<  0, 139, 139>::value,
	            darkgoldenrod       = static_rgb<184, 134,  11>::value,
	            darkgray            = static_rgb<169, 169, 169>::value,
	            darkgreen           = static_rgb<  0, 100,   0>::value,
	            darkgrey            = static_rgb<169, 169, 169>::value,
	            darkkhaki           = static_rgb<189, 183, 107>::value,
	            darkmagenta         = static_rgb<139,   0, 139>::value,
	            darkolivegreen      = static_rgb< 85, 107,  47>::value,
	            darkorange          = static_rgb<255, 140,   0>::value,
	            darkorchid          = static_rgb<153,  50, 204>::value,
	            darkred             = static_rgb<139,   0,   0>::value,
	            darksalmon          = static_rgb<233, 150, 122>::value,
	            darkseagreen        = static_rgb<143, 188, 143>::value,
	            darkslateblue       = static_rgb< 72,  61, 139>::value,
	            darkslategray       = static_rgb< 47,  79,  79>::value,
	            darkslategrey       = static_rgb< 47,  79,  79>::value,
	            darkturquoise       = static_rgb<  0, 206, 209>::value,
	            darkviolet          = static_rgb<148,   0, 211>::value,
	            deeppink            = static_rgb<255,  20, 147>::value,
	            deepskyblue         = static_rgb<  0, 191, 255>::value,
	            dimgray             = static_rgb<105, 105, 105>::value,
	            dimgrey             = static_rgb<105, 105, 105>::value,
	            dodgerblue          = static_rgb< 30, 144, 255>::value,
	            firebrick           = static_rgb<178,  34,  34>::value,
	            floralwhite         = static_rgb<255, 250, 240>::value,
	            forestgreen         = static_rgb< 34, 139,  34>::value,
	            fuchsia             = static_rgb<255,   0, 255>::value,
	            gainsboro           = static_rgb<220, 220, 220>::value,
	            ghostwhite          = static_rgb<248, 248, 255>::value,
	            gold                = static_rgb<255, 215,   0>::value,
	            goldenrod           = static_rgb<218, 165,  32>::value,
	            gray                = static_rgb<128, 128, 128>::value,
	            green               = static_rgb<  0, 128,   0>::value,
	            greenyellow         = static_rgb<173, 255,  47>::value,
	            grey                = static_rgb<128, 128, 128>::value,
	            honeydew            = static_rgb<240, 255, 240>::value,
	            hotpink             = static_rgb<255, 105, 180>::value,
	            indianred           = static_rgb<205,  92,  92>::value,
	            indigo              = static_rgb< 75,   0, 130>::value,
	            ivory               = static_rgb<255, 255, 240>::value,
	            khaki               = static_rgb<240, 230, 140>::value,
	            lavender            = static_rgb<230, 230, 250>::value,
	            lavenderblush       = static_rgb<255, 240, 245>::value,
	            lawngreen           = static_rgb<124, 252,   0>::value,
	            lemonchiffon        = static_rgb<255, 250, 205>::value,
	            lightblue           = static_rgb<173, 216, 230>::value,
	            lightcoral          = static_rgb<240, 128, 128>::value,
	            lightcyan           = static_rgb<224, 255, 255>::value,
	            lightgoldenrodyellow= static_rgb<250, 250, 210>::value,
	            lightgray           = static_rgb<211, 211, 211>::value,
	            lightgreen          = static_rgb<144, 238, 144>::value,
	            lightgrey           = static_rgb<211, 211, 211>::value,
	            lightpink           = static_rgb<255, 182, 193>::value,
	            lightsalmon         = static_rgb<255, 160, 122>::value,
	            lightseagreen       = static_rgb< 32, 178, 170>::value,
	            lightskyblue        = static_rgb<135, 206, 250>::value,
	            lightslategray      = static_rgb<119, 136, 153>::value,
	            lightslategrey      = static_rgb<119, 136, 153>::value,
	            lightsteelblue      = static_rgb<176, 196, 222>::value,
	            lightyellow         = static_rgb<255, 255, 224>::value,
	            lime                = static_rgb<  0, 255,   0>::value,
	            limegreen           = static_rgb< 50, 205,  50>::value,
	            linen               = static_rgb<250, 240, 230>::value,
	            magenta             = static_rgb<255,   0, 255>::value,
	            maroon              = static_rgb<128,   0,   0>::value,
	            mediumaquamarine    = static_rgb<102, 205, 170>::value,
	            mediumblue          = static_rgb<  0,   0, 205>::value,
	            mediumorchid        = static_rgb<186,  85, 211>::value,
	            mediumpurple        = static_rgb<147, 112, 219>::value,
	            mediumseagreen      = static_rgb< 60, 179, 113>::value,
	            mediumslateblue     = static_rgb<123, 104, 238>::value,
	            mediumspringgreen   = static_rgb<  0, 250, 154>::value,
	            mediumturquoise     = static_rgb< 72, 209, 204>::value,
	            mediumvioletred     = static_rgb<199,  21, 133>::value,
	            midnightblue        = static_rgb< 25,  25, 112>::value,
	            mintcream           = static_rgb<245, 255, 250>::value,
	            mistyrose           = static_rgb<255, 228, 225>::value,
	            moccasin            = static_rgb<255, 228, 181>::value,
	            navajowhite         = static_rgb<255, 222, 173>::value,
	            navy                = static_rgb<  0,   0, 128>::value,
	            oldlace             = static_rgb<253, 245, 230>::value,
	            olive               = static_rgb<128, 128,   0>::value,
	            olivedrab           = static_rgb<107, 142,  35>::value,
	            orange              = static_rgb<255, 165,   0>::value,
	            orangered           = static_rgb<255,  69,   0>::value,
	            orchid              = static_rgb<218, 112, 214>::value,
	            palegoldenrod       = static_rgb<238, 232, 170>::value,
	            palegreen           = static_rgb<152, 251, 152>::value,
	            paleturquoise       = static_rgb<175, 238, 238>::value,
	            palevioletred       = static_rgb<219, 112, 147>::value,
	            papayawhip          = static_rgb<255, 239, 213>::value,
	            peachpuff           = static_rgb<255, 218, 185>::value,
	            peru                = static_rgb<205, 133,  63>::value,
	            pink                = static_rgb<255, 192, 203>::value,
	            plum                = static_rgb<221, 160, 221>::value,
	            powderblue          = static_rgb<176, 224, 230>::value,
	            purple              = static_rgb<128,   0, 128>::value,
	            red                 = static_rgb<255,   0,   0>::value,
	            rosybrown           = static_rgb<188, 143, 143>::value,
	            royalblue           = static_rgb< 65, 105, 225>::value,
	            saplebrown          = static_rgb<139,  69,  19>::value,
	            salmon              = static_rgb<250, 128, 114>::value,
	            sandybrown          = static_rgb<244, 164,  96>::value,
	            seagreen            = static_rgb< 46, 139,  87>::value,
	            seashell            = static_rgb<255, 245, 238>::value,
	            sienna              = static_rgb<160,  82,  45>::value,
	            silver              = static_rgb<192, 192, 192>::value,
	            skyblue             = static_rgb<135, 206, 235>::value,
	            slateblue           = static_rgb<106,  90, 205>::value,
	            slategray           = static_rgb<112, 128, 144>::value,
	            slategrey           = static_rgb<112, 128, 144>::value,
	            snow                = static_rgb<255, 250, 250>::value,
	            springgreen         = static_rgb<  0, 255, 127>::value,
	            steelblue           = static_rgb< 70, 130, 180>::value,
	            tan                 = static_rgb<210, 180, 140>::value,
	            teal                = static_rgb<  0, 128, 128>::value,
	            thistle             = static_rgb<216, 191, 216>::value,
	            tomato              = static_rgb<255,  99,  71>::value,
	            turquoise           = static_rgb< 64, 224, 208>::value,
	            violet              = static_rgb<238, 130, 238>::value,
	            wheat               = static_rgb<245, 222, 179>::value,
	            white               = static_rgb<255, 255, 255>::value,
	            whitesmoke          = static_rgb<245, 245, 245>::value,
	            yellow              = static_rgb<255, 255,   0>::value,
	            yellowgreen         = static_rgb<154, 205,  50>::value,
	            transparent         = static_rgba<0,0,0,0>::value;
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

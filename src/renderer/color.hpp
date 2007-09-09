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


#ifndef SGE_COLOR_HPP_INCLUDED
#define SGE_COLOR_HPP_INCLUDED

#include <ostream>
#include <istream>

#include "../types.hpp"
#include "../typeswitch.hpp"

namespace sge
{

typedef uint32 color;
typedef uint8  color_element;

template<unsigned Depth> struct bit_depth_traits;
template<> struct bit_depth_traits<16> { typedef uint16 color; };
template<> struct bit_depth_traits<32> { typedef sge::color color; };
typedef bit_depth_traits<16> bit_depth16;
typedef bit_depth_traits<32> bit_depth32;

namespace color_scheme
{
	enum type {
		rgba,
		argb
	};
}

// TODO: #ifdef here
const color_scheme::type current_color_scheme = color_scheme::rgba;

template<color_scheme::type Scheme>
struct color_traits;

const unsigned color_bytes = 4;
const unsigned color_bits_per_byte = 8;

template<>
struct color_traits<color_scheme::rgba> {
	enum {
		r_pos = 0,
		g_pos = 1,
		b_pos = 2,
		a_pos = 3
	};

	template<unsigned Pos>
	struct shift_count {
		enum {
			value = Pos * color_bits_per_byte
		};
	};


	enum {
		r_shift = shift_count<r_pos>::value,
		g_shift = shift_count<g_pos>::value,
		b_shift = shift_count<b_pos>::value,
		a_shift = shift_count<a_pos>::value
	};
};

#define SGE_MAKE_COLOR(r,g,b,a) static_cast<color>(r) << color_traits<current_color_scheme>::r_shift \
                              | static_cast<color>(g) << color_traits<current_color_scheme>::g_shift \
                              | static_cast<color>(b) << color_traits<current_color_scheme>::b_shift \
                              | static_cast<color>(a) << color_traits<current_color_scheme>::a_shift

template<color_element r, color_element g, color_element b, color_element a=255>
struct static_color {
	static const color value = SGE_MAKE_COLOR(r,g,b,a);
};

inline color make_color(const color_element r, const color_element g, const color_element b, const color_element a)
{
	return SGE_MAKE_COLOR(r,g,b,a);
}

#undef SGE_MAKE_COLOR

inline color_element&   color_red(color& c) { return *(reinterpret_cast<color_element*>(&c) + color_traits<current_color_scheme>::r_pos); }
inline color_element& color_green(color& c) { return *(reinterpret_cast<color_element*>(&c) + color_traits<current_color_scheme>::g_pos); }
inline color_element&  color_blue(color& c) { return *(reinterpret_cast<color_element*>(&c) + color_traits<current_color_scheme>::b_pos); }
inline color_element& color_alpha(color& c) { return *(reinterpret_cast<color_element*>(&c) + color_traits<current_color_scheme>::a_pos); }

inline color_element   color_red(const color c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::r_pos); }
inline color_element color_green(const color c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::g_pos); }
inline color_element  color_blue(const color c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::b_pos); }
inline color_element color_alpha(const color c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::a_pos); }


namespace colors {
	const color aliceblue           = static_color<240, 248, 255>::value,
	            antiquewhite        = static_color<250, 235, 215>::value,
	            aqua                = static_color<0  , 255, 255>::value,
	            aquamarine          = static_color<127, 255, 212>::value,
	            azure               = static_color<240, 255, 255>::value,
	            beige               = static_color<245, 245, 220>::value,
	            bisque              = static_color<255, 228, 196>::value,
	            black               = static_color<  0,   0,   0>::value,
	            blanchedalmond      = static_color<255, 235, 205>::value,
	            blue                = static_color<  0,   0, 255>::value,
	            blueviolet          = static_color<138,  43, 226>::value,
	            brown               = static_color<165,  42,  42>::value,
	            burlywood           = static_color<222, 184, 135>::value,
	            cadetblue           = static_color< 95, 158, 160>::value,
	            chartreuse          = static_color<127, 255,   0>::value,
	            chocolate           = static_color<210, 105,  30>::value,
	            coral               = static_color<255, 127,  80>::value,
	            cornflowerblue      = static_color<100, 149, 237>::value,
	            cornsilk            = static_color<255, 248, 220>::value,
	            crimson             = static_color<220,  20,  60>::value,
	            cyan                = static_color<  0, 255, 255>::value,
	            darkblue            = static_color<  0,   0, 139>::value,
	            darkcyan            = static_color<  0, 139, 139>::value,
	            darkgoldenrod       = static_color<184, 134,  11>::value,
	            darkgray            = static_color<169, 169, 169>::value,
	            darkgreen           = static_color<  0, 100,   0>::value,
	            darkgrey            = static_color<169, 169, 169>::value,
	            darkkhaki           = static_color<189, 183, 107>::value,
	            darkmagenta         = static_color<139,   0, 139>::value,
	            darkolivegreen      = static_color< 85, 107,  47>::value,
	            darkorange          = static_color<255, 140,   0>::value,
	            darkorchid          = static_color<153,  50, 204>::value,
	            darkred             = static_color<139,   0,   0>::value,
	            darksalmon          = static_color<233, 150, 122>::value,
	            darkseagreen        = static_color<143, 188, 143>::value,
	            darkslateblue       = static_color< 72,  61, 139>::value,
	            darkslategray       = static_color< 47,  79,  79>::value,
	            darkslategrey       = static_color< 47,  79,  79>::value,
	            darkturquoise       = static_color<  0, 206, 209>::value,
	            darkviolet          = static_color<148,   0, 211>::value,
	            deeppink            = static_color<255,  20, 147>::value,
	            deepskyblue         = static_color<  0, 191, 255>::value,
	            dimgray             = static_color<105, 105, 105>::value,
	            dimgrey             = static_color<105, 105, 105>::value,
	            dodgerblue          = static_color< 30, 144, 255>::value,
	            firebrick           = static_color<178,  34,  34>::value,
	            floralwhite         = static_color<255, 250, 240>::value,
	            forestgreen         = static_color< 34, 139,  34>::value,
	            fuchsia             = static_color<255,   0, 255>::value,
	            gainsboro           = static_color<220, 220, 220>::value,
	            ghostwhite          = static_color<248, 248, 255>::value,
	            gold                = static_color<255, 215,   0>::value,
	            goldenrod           = static_color<218, 165,  32>::value,
	            gray                = static_color<128, 128, 128>::value,
	            green               = static_color<  0, 128,   0>::value,
	            greenyellow         = static_color<173, 255,  47>::value,
	            grey                = static_color<128, 128, 128>::value,
	            honeydew            = static_color<240, 255, 240>::value,
	            hotpink             = static_color<255, 105, 180>::value,
	            indianred           = static_color<205,  92,  92>::value,
	            indigo              = static_color< 75,   0, 130>::value,
	            ivory               = static_color<255, 255, 240>::value,
	            khaki               = static_color<240, 230, 140>::value,
	            lavender            = static_color<230, 230, 250>::value,
	            lavenderblush       = static_color<255, 240, 245>::value,
	            lawngreen           = static_color<124, 252,   0>::value,
	            lemonchiffon        = static_color<255, 250, 205>::value,
	            lightblue           = static_color<173, 216, 230>::value,
	            lightcoral          = static_color<240, 128, 128>::value,
	            lightcyan           = static_color<224, 255, 255>::value,
	            lightgoldenrodyellow= static_color<250, 250, 210>::value,
	            lightgray           = static_color<211, 211, 211>::value,
	            lightgreen          = static_color<144, 238, 144>::value,
	            lightgrey           = static_color<211, 211, 211>::value,
	            lightpink           = static_color<255, 182, 193>::value,
	            lightsalmon         = static_color<255, 160, 122>::value,
	            lightseagreen       = static_color< 32, 178, 170>::value,
	            lightskyblue        = static_color<135, 206, 250>::value,
	            lightslategray      = static_color<119, 136, 153>::value,
	            lightslategrey      = static_color<119, 136, 153>::value,
	            lightsteelblue      = static_color<176, 196, 222>::value,
	            lightyellow         = static_color<255, 255, 224>::value,
	            lime                = static_color<  0, 255,   0>::value,
	            limegreen           = static_color< 50, 205,  50>::value,
	            linen               = static_color<250, 240, 230>::value,
	            magenta             = static_color<255,   0, 255>::value,
	            maroon              = static_color<128,   0,   0>::value,
	            mediumaquamarine    = static_color<102, 205, 170>::value,
	            mediumblue          = static_color<  0,   0, 205>::value,
	            mediumorchid        = static_color<186,  85, 211>::value,
	            mediumpurple        = static_color<147, 112, 219>::value,
	            mediumseagreen      = static_color< 60, 179, 113>::value,
	            mediumslateblue     = static_color<123, 104, 238>::value,
	            mediumspringgreen   = static_color<  0, 250, 154>::value,
	            mediumturquoise     = static_color< 72, 209, 204>::value,
	            mediumvioletred     = static_color<199,  21, 133>::value,
	            midnightblue        = static_color< 25,  25, 112>::value,
	            mintcream           = static_color<245, 255, 250>::value,
	            mistyrose           = static_color<255, 228, 225>::value,
	            moccasin            = static_color<255, 228, 181>::value,
	            navajowhite         = static_color<255, 222, 173>::value,
	            navy                = static_color<  0,   0, 128>::value,
	            oldlace             = static_color<253, 245, 230>::value,
	            olive               = static_color<128, 128,   0>::value,
	            olivedrab           = static_color<107, 142,  35>::value,
	            orange              = static_color<255, 165,   0>::value,
	            orangered           = static_color<255,  69,   0>::value,
	            orchid              = static_color<218, 112, 214>::value,
	            palegoldenrod       = static_color<238, 232, 170>::value,
	            palegreen           = static_color<152, 251, 152>::value,
	            paleturquoise       = static_color<175, 238, 238>::value,
	            palevioletred       = static_color<219, 112, 147>::value,
	            papayawhip          = static_color<255, 239, 213>::value,
	            peachpuff           = static_color<255, 218, 185>::value,
	            peru                = static_color<205, 133,  63>::value,
	            pink                = static_color<255, 192, 203>::value,
	            plum                = static_color<221, 160, 221>::value,
	            powderblue          = static_color<176, 224, 230>::value,
	            purple              = static_color<128,   0, 128>::value,
	            red                 = static_color<255,   0,   0>::value,
	            rosybrown           = static_color<188, 143, 143>::value,
	            royalblue           = static_color< 65, 105, 225>::value,
	            saplebrown          = static_color<139,  69,  19>::value,
	            salmon              = static_color<250, 128, 114>::value,
	            sandybrown          = static_color<244, 164,  96>::value,
	            seagreen            = static_color< 46, 139,  87>::value,
	            seashell            = static_color<255, 245, 238>::value,
	            sienna              = static_color<160,  82,  45>::value,
	            silver              = static_color<192, 192, 192>::value,
	            skyblue             = static_color<135, 206, 235>::value,
	            slateblue           = static_color<106,  90, 205>::value,
	            slategray           = static_color<112, 128, 144>::value,
	            slategrey           = static_color<112, 128, 144>::value,
	            snow                = static_color<255, 250, 250>::value,
	            springgreen         = static_color<  0, 255, 127>::value,
	            steelblue           = static_color< 70, 130, 180>::value,
	            tan                 = static_color<210, 180, 140>::value,
	            teal                = static_color<  0, 128, 128>::value,
	            thistle             = static_color<216, 191, 216>::value,
	            tomato              = static_color<255,  99,  71>::value,
	            turquoise           = static_color< 64, 224, 208>::value,
	            violet              = static_color<238, 130, 238>::value,
	            wheat               = static_color<245, 222, 179>::value,
	            white               = static_color<255, 255, 255>::value,
	            whitesmoke          = static_color<245, 245, 245>::value,
	            yellow              = static_color<255, 255,   0>::value,
	            yellowgreen         = static_color<154, 205,  50>::value,
	            transparent         = static_color<  0,   0,   0, 0>::value;
}

struct color4 {
	typedef space_unit value_type;
	color4(const value_type r = 0, const value_type g = 0, const value_type b = 0, const value_type a = 0)
	: r(r), g(g), b(b), a(a) {}

	value_type r,g,b,a;
};

const color4::value_type color_to_color4_factor = 255;

inline color4::value_type   red_part_rgba_f(const color c) { return color_red(c)   / color_to_color4_factor; }
inline color4::value_type green_part_rgba_f(const color c) { return color_green(c) / color_to_color4_factor; }
inline color4::value_type  blue_part_rgba_f(const color c) { return color_blue(c)  / color_to_color4_factor; }
inline color4::value_type alpha_part_rgba_f(const color c) { return color_alpha(c) / color_to_color4_factor; }


inline std::ostream& operator<< (std::ostream& os, const color4& col)
{
	return os << '(' << col.r << ',' << col.g << ',' << col.b << ',' << col.a << ')';
}

inline std::wostream& operator<< (std::wostream& os, const color4& col)
{
	return os << L'(' << col.r << L',' << col.g << L',' << col.b << L',' << col.a << L')';
}

inline std::istream& operator>> (std::istream& s, color4& col)
{
	char c;
	s >> c;
	if(c != '(')
		s.setstate(std::ios_base::failbit);

	color4::value_type r,g,b,a;
	s >> r >> c;
	if (c != ',')
		s.setstate(std::ios_base::failbit);
	s >> g >> c;
	if (c != ',')
		s.setstate(std::ios_base::failbit);
	s >> b >> c;
	if (c != ',')
		s.setstate(std::ios_base::failbit);
	s >> a >> c;
	if (c != ')')
		s.setstate(std::ios_base::failbit);
	
	col = color4(r,g,b,a);

	return s;
}

inline std::wistream& operator>> (std::wistream& s, color4& col)
{
	wchar_t c;
	s >> c;
	if(c != L'(')
		s.setstate(std::ios_base::failbit);

	color4::value_type r,g,b,a;
	s >> r >> c;
	if (c != L',')
		s.setstate(std::ios_base::failbit);
	s >> g >> c;
	if (c != L',')
		s.setstate(std::ios_base::failbit);
	s >> b >> c;
	if (c != L',')
		s.setstate(std::ios_base::failbit);
	s >> a >> c;
	if (c != L')')
		s.setstate(std::ios_base::failbit);
	
	col = color4(r,g,b,a);

	return s;
}

inline color4 color_to_color4(const color c)
{
	return color4(red_part_rgba_f(c), green_part_rgba_f(c), blue_part_rgba_f(c), alpha_part_rgba_f(c));
}

inline color color4_to_color(const color4 c)
{
	return make_color(color_element(c.r * color_to_color4_factor),color_element(c.g * color_to_color4_factor),color_element(c.b * color_to_color4_factor),color_element(c.a * color_to_color4_factor));
}

// TODO
inline color sge_to_rgba(const color c)
{
	return c;
}

inline color sge_to_argb(const color c)
{
	return c;
}

inline color sge_to_bgra(const color c)
{
	return c;
}

/*inline color rgba_to_sge(const color c)
{
	return (c >> 8) | ((c & 0xFF) << 24);
}

inline color argb_to_sge(const color c)
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
}*/

}

#endif

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
#include "../stub.hpp"

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
const color_element color_element_max = 255;

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

template<color_element r, color_element g, color_element b, color_element a = color_element_max>
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

inline color_element   color_red(const color& c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::r_pos); }
inline color_element color_green(const color& c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::g_pos); }
inline color_element  color_blue(const color& c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::b_pos); }
inline color_element color_alpha(const color& c) { return *(reinterpret_cast<const color_element*>(&c) + color_traits<current_color_scheme>::a_pos); }

struct color4 {
	typedef space_unit value_type;
	color4(const value_type r = 0, const value_type g = 0, const value_type b = 0, const value_type a = 0)
	: r(r), g(g), b(b), a(a) {}

	value_type r,g,b,a;
};

const color4::value_type color_to_color4_factor = 255;

inline color4::value_type   red_part_rgba_f(const color c) { return static_cast<color4::value_type>(color_red(c))   / color_to_color4_factor; }
inline color4::value_type green_part_rgba_f(const color c) { return static_cast<color4::value_type>(color_green(c)) / color_to_color4_factor; }
inline color4::value_type  blue_part_rgba_f(const color c) { return static_cast<color4::value_type>(color_blue(c))  / color_to_color4_factor; }
inline color4::value_type alpha_part_rgba_f(const color c) { return static_cast<color4::value_type>(color_alpha(c)) / color_to_color4_factor; }

template<typename Ch,typename Traits>
inline std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &s, const color4 &col)
{
	return s << s.widen('(') << col.r << s.widen(',') << col.g << s.widen(',') << col.b << s.widen(',') << col.a << s.widen(')');
}

template<typename Ch,typename Traits>
inline std::basic_istream<Ch,Traits>& operator>> (std::basic_istream<Ch,Traits>& s, color4& col)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
		s.setstate(std::ios_base::failbit);

	color4::value_type r,g,b,a;
	s >> r >> c;
	if (c != s.widen(','))
		s.setstate(std::ios_base::failbit);
	s >> g >> c;
	if (c != s.widen(','))
		s.setstate(std::ios_base::failbit);
	s >> b >> c;
	if (c != s.widen(','))
		s.setstate(std::ios_base::failbit);
	s >> a >> c;
	if (c != s.widen(')'))
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

// FIXME
inline color sge_to_rgba(const color c)
{
	SGE_STUB_FUNCTION
	return c;
}

inline color sge_to_argb(const color c)
{
	SGE_STUB_FUNCTION
	return c;
}

inline color sge_to_bgra(const color c)
{
	SGE_STUB_FUNCTION
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

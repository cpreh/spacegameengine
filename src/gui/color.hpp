/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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


#ifndef SGE_GUI_COLOR_HPP_INCLUDED
#define SGE_GUI_COLOR_HPP_INCLUDED

#include <boost/function.hpp>

namespace sge {
namespace gui {

namespace mixing_policy { class normal; }

class color {
	typedef unsigned char channel_t;
	static const unsigned int FIELD_BITS = 8;
	static const unsigned int FIELD_MASK = (1U << FIELD_BITS) - 1;
	static const unsigned int MAX_VALUE = FIELD_MASK;
	typedef boost::function<void(color&, const color&)> mixing_policy_t;
	typedef boost::function<color(const color &col1, const color &col2, float percentage)> gradient_policy_t;
	channel_t r, g, b, a;

// TODO: uncomment or delete?
//	color() : r(0), g(0), b(0), a(255) {}
//	color(channel_t r, channel_t g, channel_t b, channel_t a = MAX_VALUE)
//		: r(r), g(g), b(b), a(a) {}
//	color(float r, float g, float b, float a = 1.0)
//		: r(r*MAX_VALUE), g(g*MAX_VALUE), b(b*MAX_VALUE), a(a*MAX_VALUE) {}

	inline void mix(mixing_policy_t policy, const color &other) {
		policy(*this, other);
	}

	template <typename MixingPolicy = mixing_policy::normal> inline void mix(const color &other) {
		mix(&MixingPolicy::mixin, other);
	}

	template <typename MixingPolicy = mixing_policy::normal> inline void mix(color other, float opacity) {
		color.a = (MAX_VALUE * opacity) + .5;
		mix<MixingPolicy>(other);
	}

	inline sge::color rgba() const {
		return (r << 3*FIELD_BITS) | (g << 2*FIELD_BITS) |
		       (b <<   FIELD_BITS) | a;
	}

	inline sge::color argb() const {
		return (a << 3*FIELD_BITS) | (r << 2*FIELD_BITS) |
		       (g <<   FIELD_BITS) | b;
	}

	inline void rgba(sge::color c) {
		a = c & FIELD_MASK; b = (c >>= FIELD_BITS) & FIELD_MASK;
		g = (c >>= FIELD_BITS) & FIELD_MASK; r = c >>= FIELD_BITS;
	}

	inline void argb(sge::color c) {
		b = c & FIELD_MASK; g = (c >>= FIELD_BITS) & FIELD_MASK;
		r = (c >>= FIELD_BITS) & FIELD_MASK; a = c >>= FIELD_BITS;
	}
};

#include "mixing_policies.hpp"

}
}

#endif // SGE_GUI_COLOR_HPP_INCLUDED

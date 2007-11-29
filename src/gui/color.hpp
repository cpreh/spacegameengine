/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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


#ifndef SGE_GUI_COLOR_HPP_INCLUDED
#define SGE_GUI_COLOR_HPP_INCLUDED

#include <boost/function.hpp>

#include "../renderer/color.hpp"

namespace sge {
namespace gui {

struct color {
	typedef unsigned char channel_t;
	static const channel_t MAX_VALUE = (1 << sge::color_bits_per_byte) - 1;
	typedef boost::function<void(color&, const color&)> mixing_policy_t;
	typedef boost::function<color(const color &col1, const color &col2, float percentage)> gradient_policy_t;
	channel_t r, g, b, a;

	color() : r(0), g(0), b(0), a(MAX_VALUE) {}
	color(channel_t r, channel_t g, channel_t b, channel_t a = MAX_VALUE)
		: r(r), g(g), b(b), a(a) {}
	color(const sge::color c) : r(sge::color_red(c)), g(sge::color_green(c)), b(sge::color_blue(c)), a(sge::color_alpha(c)) {}

	inline void mix(mixing_policy_t policy, const color &other) {
		policy(*this, other);
	}

	template <typename MixingPolicy> inline void mix(const color &other) {
		mix(MixingPolicy(), other);
	}

	template <typename MixingPolicy> inline void mix(color other, float opacity) {
		// TODO: Change: first mix, then change opacity
		other.a = static_cast<channel_t>((static_cast<float>(MAX_VALUE) * opacity) + .5);
		mix<MixingPolicy>(other);
	}

	inline operator sge::color() const {
		return sge::make_color(r, g, b, a);
	}

	inline static color from_float(float r, float g, float b, float a = 1.0) {
		return color(
			static_cast<channel_t>(r*MAX_VALUE),
			static_cast<channel_t>(g*MAX_VALUE),
			static_cast<channel_t>(b*MAX_VALUE),
			static_cast<channel_t>(a*MAX_VALUE)
		);
	}

};

}
}

#include "mixing_policies.hpp"

#endif // SGE_GUI_COLOR_HPP_INCLUDED

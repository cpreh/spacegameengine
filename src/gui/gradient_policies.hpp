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


#ifndef SGE_GUI_GRADIENT_POLICIES_HPP_INCLUDED
#define SGE_GUI_GRADIENT_POLICIES_HPP_INCLUDED

#include "color.hpp"

namespace sge {
namespace gui {
namespace gradient_policy {

struct normal {
	static color mix(const color &col1, const color &col2, float percentage) {
		return color(
			static_cast<color::channel_t>((1-percentage) * col1.r + percentage * col2.r + 0.5),
			static_cast<color::channel_t>((1-percentage) * col1.g + percentage * col2.g + 0.5),
			static_cast<color::channel_t>((1-percentage) * col1.b + percentage * col2.b + 0.5),
			static_cast<color::channel_t>((1-percentage) * col1.a + percentage * col2.a + 0.5)
		);
	}

	color operator()(const color &col1, const color &col2, float percentage) const {
		return mix(col1, col2, percentage);
	}
};

template<typename T=normal> struct
	there_and_back_again // a hobbits tale
{
	T gradpol;
	there_and_back_again(const T &gradpol = T()) : gradpol(gradpol) {}

	static color mix(const T &gradpol, const color &col1, const color &col2, float percentage) {
		return gradpol(col1, col2, 2 * ((percentage > 0.5) ? 1-percentage : percentage));
	}

	color operator()(const color &col1, const color &col2, float percentage) const {
		return mix(gradpol, col1, col2, percentage);
	}
};



// TODO: HSL CW, HSL CCW, ...

}
}
}

#endif // SGE_GUI_GRADIENT_POLICIES_HPP_INCLUDED


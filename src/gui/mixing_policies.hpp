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


#ifndef SGE_GUI_MIXING_POLICIES_HPP_INCLUDED
#define SGE_GUI_MIXING_POLICIES_HPP_INCLUDED

#include "color.hpp"

namespace sge {
namespace gui {
namespace mixing_policy {

class normal {
	static color mix(const color &col1, const color &col2) {
		unsigned long r, g, b;

		if (col2.a == 0) return col1;
		if (col2.a == color::MAX_VALUE) return col2;

		const unsigned int factor1 = col1.a * (color::MAX_VALUE - col2.a);
		const unsigned int factor2 = col2.a * 255;
		const unsigned int factorsum = factor1 + factor2;

		color ret = { //                           v-int division w/ round()-v
			(factor1 * col1.r + factor2 * col2.r + factorsum / 2) / factorsum,
			(factor1 * col1.g + factor2 * col2.g + factorsum / 2) / factorsum,
			(factor1 * col1.b + factor2 * col2.b + factorsum / 2) / factorsum,
			col1.a + ((color::MAX_VALUE - col1.a) * col2.a + color::MAX_VALUE / 2) / color::MAX_VALUE
		};
		return ret;
	}

	static inline void mixin(color &col1, const color &col2) {
		col1 = mix(col1, col2);
	}
};

// TODO: Additive, subtractive, ...

}
}
}

#endif // SGE_GUI_MIXING_POLICIES_HPP_INCLUDED

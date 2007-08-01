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
public:
	static color mix(const color &col1, const color &col2) {
		if (col2.a == 0) return col1;
		if (col2.a == color::MAX_VALUE) return col2;

		const unsigned int factor1 = col1.a * (color::MAX_VALUE - col2.a);
		const unsigned int factor2 = col2.a * color::MAX_VALUE;
		const unsigned int factorsum = factor1 + factor2;

		return color( //                           v-int division w/ round()-v
			(factor1 * col1.r + factor2 * col2.r + factorsum / 2) / factorsum,
			(factor1 * col1.g + factor2 * col2.g + factorsum / 2) / factorsum,
			(factor1 * col1.b + factor2 * col2.b + factorsum / 2) / factorsum,
			col1.a + ((color::MAX_VALUE - col1.a) * col2.a + color::MAX_VALUE / 2) / color::MAX_VALUE
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class replace {
public:
	static color mix(const color &, const color &col2) {
		return col2;
	}

	void operator()(color &col1, const color &col2) const {
		col1 = col2;
	}
};

class additive {
	static inline color::channel_t additive_cropped(const color::channel_t a, const color::channel_t b, const float alpha) {
		const float val = a + (b * alpha) + 0.5;
		return (val > color::MAX_VALUE) ? color::MAX_VALUE : static_cast<color::channel_t>(val);
	}
public:
	static color mix(const color &col1, const color &col2) {
		const float alpha = float(col2.a) / color::MAX_VALUE;
		return color(
			additive_cropped(col1.r, col2.r, alpha),
			additive_cropped(col1.g, col2.g, alpha),
			additive_cropped(col1.b, col2.b, alpha),
			col1.a
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class subtractive {
	static inline color::channel_t subtract_cropped(const color::channel_t a, const color::channel_t b, const float alpha) {
		const float val = a - (b * alpha) + 0.5;
		return (val < 0) ? 0 : static_cast<color::channel_t>(val);
	}
public:
	static color mix(const color &col1, const color &col2) {
		const float alpha = float(col2.a) / color::MAX_VALUE;
		return color(
			subtract_cropped(col1.r, col2.r, alpha),
			subtract_cropped(col1.g, col2.g, alpha),
			subtract_cropped(col1.b, col2.b, alpha),
			col1.a
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class subtractive_reverse {
	static inline color::channel_t subtract_cropped(const color::channel_t a, const color::channel_t b, const float alpha) {
		const float val = a - (b * alpha) + 0.5;
		return (val < 0) ? 0 : static_cast<color::channel_t>(val);
	}
public:
	static color mix(const color &col1, const color &col2) {
		const float alpha = float(col1.a) / color::MAX_VALUE;
		return color(
			subtract_cropped(col2.r, col1.r, alpha),
			subtract_cropped(col2.g, col1.g, alpha),
			subtract_cropped(col2.b, col1.b, alpha),
			col2.a
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class multiply_rgb {
	static inline color::channel_t multiply_impl(const color::channel_t a, const color::channel_t b, const float alpha) {
		return static_cast<color::channel_t>(
			(a * (b + ((color::MAX_VALUE - b) * alpha)) + 0.5) / color::MAX_VALUE
		);
	}
public:
	static color mix(const color &col1, const color &col2) {
		const float alpha = float(col2.a) / color::MAX_VALUE;
		return color(
			multiply_impl(col1.r, col2.r, alpha),
			multiply_impl(col1.r, col2.r, alpha),
			multiply_impl(col1.r, col2.r, alpha),
			col1.a
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class multiply_rgba {
	static inline color::channel_t multiply_impl(const color::channel_t a, const color::channel_t b) {
		return (a*b + color::MAX_VALUE*color::MAX_VALUE/2) / color::MAX_VALUE*color::MAX_VALUE;
	}
public:
	static color mix(const color &col1, const color &col2) {
		return color(
			multiply_impl(col1.r, col2.r),
			multiply_impl(col1.g, col2.g),
			multiply_impl(col1.b, col2.b),
			multiply_impl(col1.a, col2.a)
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class brighten {
	static inline color::channel_t brighten_impl(const color::channel_t a, const float alpha) {
		return a + static_cast<color::channel_t>((color::MAX_VALUE - a) * alpha + 0.5);
	}
public:
	static color mix(const color &col1, const color &col2) {
		const float alpha = float(col2.a) / color::MAX_VALUE;
		return color(
			brighten_impl(col1.r, alpha),
			brighten_impl(col1.g, alpha),
			brighten_impl(col1.b, alpha),
			col1.a
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

class darken {
	static inline color::channel_t darken_impl(const color::channel_t a, const float alpha) {
		return static_cast<color::channel_t>(a * alpha + 0.5);
	}
public:
	static color mix(const color &col1, const color &col2) {
		const float alpha = float(col2.a) / color::MAX_VALUE;
		return color(
			darken_impl(col1.r, alpha),
			darken_impl(col1.g, alpha),
			darken_impl(col1.b, alpha),
			col1.a
		);
	}

	void operator()(color &col1, const color &col2) const {
		col1 = mix(col1, col2);
	}
};

}
}
}

#endif // SGE_GUI_MIXING_POLICIES_HPP_INCLUDED

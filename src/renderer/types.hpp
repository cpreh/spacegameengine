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


#ifndef SGE_RENDERER_TYPES_HPP_INCLUDED
#define SGE_RENDERER_TYPES_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <ostream>
#include "../types.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "color.hpp"

namespace sge
{

namespace bit_depth
{
	enum type {
		depth16,
		depth32
	};
}

unsigned bit_depth_bit_count(const bit_depth::type d);

typedef int                              pixel_unit;
typedef unsigned                         screen_unit;
typedef math::basic_vector<pixel_unit,2> pixel_pos_t;
typedef math::basic_dim<screen_unit,2>   screen_size_t;

struct display_mode {
	display_mode(screen_unit width, screen_unit height, bit_depth::type depth, unsigned refresh_rate = 0);
	
	screen_size_t   size;
	bit_depth::type depth;
	unsigned        refresh_rate;

	screen_unit width() const;
	screen_unit height() const;
};

std::ostream& operator<< (std::ostream& s, const display_mode& mode);
std::wostream& operator<< (std::wostream& s, const display_mode& mode);

inline bool operator== (const display_mode& l, const display_mode& r)
{
	return l.depth == r.depth && l.size == r.size && l.refresh_rate == r.refresh_rate;
}

inline bool operator!= (const display_mode& l, const display_mode& r)
{
	return !(l==r);
}

typedef unsigned multi_sample_type;


typedef std::vector<display_mode> display_mode_array;
struct renderer_caps {
	unsigned adapter_number;
	std::string driver_name;
	std::string description;
	display_mode_array display_modes;
	unsigned max_tex_size;
	unsigned max_anisotropy_level;
};

namespace resource_flags
{
	enum type {
		none,
		dynamic     = 1,
		write_only  = 1 << 1,
		default_    = write_only
	};
}
typedef unsigned resource_flag_t; // FIXME

namespace lock_flags
{
	enum type {
		none,
		discard,
		default_ = discard
	};
}
typedef unsigned lock_flag_t; // FIXME

typedef math::vector2  tex_pos;
typedef math::vector2  pos2;
typedef math::vector3  pos3;

namespace min_filter
{
	enum type {
		point,
		linear,
		mipmap,
		trilinear
	};
}

namespace mag_filter
{
	enum type {
		point,
		linear
	};
}

struct filter_args {
	typedef unsigned anisotropy_level_type;

	filter_args(const min_filter::type min_filter,
	            const mag_filter::type mag_filter,
	            const anisotropy_level_type anisotropy_level = 0)
	 : min_filter(min_filter),
	   mag_filter(mag_filter),
	   anisotropy_level(anisotropy_level)
	{}

	min_filter::type      min_filter;
	mag_filter::type      mag_filter;
	anisotropy_level_type anisotropy_level;
};

const filter_args linear_filter(min_filter::linear, mag_filter::linear),
                  point_filter(min_filter::point, mag_filter::point),
                  mip_filter(min_filter::mipmap, mag_filter::linear),
                  trilinear_filter(min_filter::trilinear, mag_filter::linear);

typedef std::size_t stage_type;

struct viewport {
	screen_unit x, y, w, h;

	viewport(const screen_unit x, const screen_unit y, const screen_unit w, const screen_unit h)
	 : x(x), y(y), w(w), h(h)
	{}
};

struct material {
	material(const color4 diffuse = color4(), const color4 ambient = color4(),
	         const color4 specular = color4(), const color4 emissive = color4(),
	         const space_unit power = 0)
	 : diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), power(power) {}
	color4     diffuse;
	color4     ambient; 
	color4     specular; 
	color4     emissive; 
	space_unit power; 
};



}

#endif

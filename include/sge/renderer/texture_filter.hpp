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


#ifndef SGE_TEXTURE_FILTER_HPP_INCLUDED
#define SGE_TEXTURE_FILTER_HPP_INCLUDED

#include "../export.hpp"

namespace sge
{

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

	SGE_SYMBOL filter_args(const min_filter::type min_filter,
	                       const mag_filter::type mag_filter,
	                       const anisotropy_level_type anisotropy_level = 0);

	min_filter::type      min_filter;
	mag_filter::type      mag_filter;
	anisotropy_level_type anisotropy_level;
};

const filter_args linear_filter(min_filter::linear, mag_filter::linear),
                  point_filter(min_filter::point, mag_filter::point),
                  mip_filter(min_filter::mipmap, mag_filter::linear),
                  trilinear_filter(min_filter::trilinear, mag_filter::linear);
}

#endif

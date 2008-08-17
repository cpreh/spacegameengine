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


#include <sge/renderer/texture_filter.hpp>

sge::renderer::filter_args::filter_args(
	const min_filter::type min_filter,
	const mag_filter::type mag_filter,
	const anisotropy_level_type anisotropy_level)
 : min_filter(min_filter),
   mag_filter(mag_filter),
   anisotropy_level(anisotropy_level)
{}

sge::renderer::filter_args const
sge::renderer::linear_filter(min_filter::linear, mag_filter::linear);

sge::renderer::filter_args const
sge::renderer::point_filter(min_filter::point, mag_filter::point);

sge::renderer::filter_args const
sge::renderer::mip_filter(min_filter::mipmap, mag_filter::linear);

sge::renderer::filter_args const
sge::renderer::trilinear_filter(min_filter::trilinear, mag_filter::linear);

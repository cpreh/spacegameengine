/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_VIEW_DECLARE_MAKE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_DECLARE_MAKE_HPP_INCLUDED

#include <sge/image/dim_fwd.hpp>
#include <sge/image/pitch_fwd.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/object.hpp>


#define SGE_IMAGE_VIEW_DECLARE_MAKE(\
	tag\
)\
extern \
template \
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
sge::image::view::object< \
	tag \
> \
sge::image::view::make( \
	sge::image::raw_pointer, \
	sge::image::dim< \
		tag \
	> const &, \
	sge::image::traits::pixel::format< \
		sge::image::traits::image::color_tag< \
			tag \
		> \
	>, \
	sge::image::pitch< \
		tag \
	> const & \
)

#endif

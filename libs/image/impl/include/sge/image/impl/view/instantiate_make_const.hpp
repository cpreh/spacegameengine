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


#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/image/pitch_fwd.hpp>
#include <sge/image/impl/view/make_const_impl.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/const_object.hpp>


#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_CONST(\
	Tag\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
sge::image::view::const_object<\
	Tag\
> \
sge::image::view::make_const< \
	Tag \
>( \
	sge::image::const_raw_pointer const, \
	sge::image::dim<\
		Tag\
	> const &,\
	sge::image::traits::pixel::format< \
		sge::image::traits::image::color_tag< \
			Tag \
		> \
	>, \
	sge::image::pitch<\
		Tag\
	> const &\
)

#endif

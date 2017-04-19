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


#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/impl/view/checked_sub_impl.hpp>
#include <sge/image/impl/view/instantiate_const_nonconst.hpp>
#include <sge/src/core/export_function_instantiation.hpp>


#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB_BASE(\
	tag,\
	view_type\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::view::view_type<\
	tag\
> \
sge::image::view::checked_sub<\
	tag\
>(\
	sge::image::view::view_type<\
		tag\
	> const &,\
	sge::image::box<\
		tag\
	> const &\
)

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB(\
	tag\
)\
SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_NONCONST(\
	tag,\
	SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CHECKED_SUB_BASE\
)

#endif

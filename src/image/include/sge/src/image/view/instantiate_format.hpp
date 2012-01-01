/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_VIEW_INSTANTIATE_FORMAT_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_INSTANTIATE_FORMAT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/src/image/view/format_impl.hpp>
#include <sge/src/image/view/instantiate_const_nonconst.hpp>
#include <fcppt/export_symbol.hpp>


#define SGE_SRC_IMAGE_VIEW_INSTANTIATE_FORMAT_BASE(\
	tag,\
	view_type\
)\
template \
FCPPT_EXPORT_SYMBOL \
sge::image::color::format::type \
sge::image::view::format<\
	tag\
>(\
	sge::image::traits::view_type<\
		tag\
	>::type const &\
);

#define SGE_SRC_IMAGE_VIEW_INSTANTIATE_FORMAT(\
	tag\
)\
SGE_SRC_IMAGE_VIEW_INSTANTIATE_CONST_NONCONST(\
	tag,\
	SGE_SRC_IMAGE_VIEW_INSTANTIATE_FORMAT_BASE\
)

#endif

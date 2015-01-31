/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_IMPL_HPP_INCLUDED

#include <sge/src/image/color/dynamic/format/object_base_impl.hpp>
#include <sge/src/image/color/dynamic/format/object_decl.hpp>
#include <mizuiro/size_type.hpp>


template<
	typename Space,
	typename BaseType,
	mizuiro::size_type NumChannels
>
template<
	typename Layout
>
sge::image::color::dynamic::format::object<
	Space,
	BaseType,
	NumChannels
>::object(
	Layout const &_layout,
	color_format_type const _color_format
)
:
	base(
		_layout
	),
	color_format(
		_color_format
	)
{
}

template<
	typename Space,
	typename BaseType,
	mizuiro::size_type NumChannels
>
sge::image::color::dynamic::format::object<
	Space,
	BaseType,
	NumChannels
>::~object()
{
}

#endif

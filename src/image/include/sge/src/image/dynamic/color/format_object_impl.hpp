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


#ifndef SGE_SRC_IMAGE_DYNAMIC_COLOR_FORMAT_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_COLOR_FORMAT_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/src/image/dynamic/color/available_layouts.hpp>
#include <sge/src/image/dynamic/color/format_object_decl.hpp>
#include <mizuiro/color/homogenous_dynamic_impl.hpp>


template<
	typename BaseType,
	unsigned NumChannels
>
sge::image::dynamic::color::format_object<
	BaseType,
	NumChannels
>::format_object(
	channel_array const &_channels,
	sge::image::dynamic::color::available_layouts::type const _layout_type,
	sge::image::color::format::type const _color_format
)
:
	base(
		_channels
	),
	layout_type(
		_layout_type
	),
	color_format(
		_color_format
	)
{
}

#endif

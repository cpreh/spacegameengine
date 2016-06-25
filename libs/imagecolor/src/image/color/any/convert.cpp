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


#include <sge/image/mizuiro_color.hpp>
#include <sge/image/color/a8_format.hpp>
#include <sge/image/color/bgr32f_format.hpp>
#include <sge/image/color/bgr8_format.hpp>
#include <sge/image/color/bgra32f_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/bgrx8_format.hpp>
#include <sge/image/color/l8_format.hpp>
#include <sge/image/color/la8_format.hpp>
#include <sge/image/color/r32f_format.hpp>
#include <sge/image/color/rgb32f_format.hpp>
#include <sge/image/color/rgb8_format.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/rgbx8_format.hpp>
#include <sge/image/color/srgb8_format.hpp>
#include <sge/image/color/srgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/src/core/export_function_instantiation.hpp>
#include <sge/src/image/color/instantiate_format.hpp>
#include <sge/src/image/color/any/convert_visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>


template<
	typename Dest
>
sge::image::mizuiro_color<
	Dest
>
sge::image::color::any::convert(
	sge::image::color::any::object const &_color
)
{
	return
		fcppt::variant::apply_unary(
			sge::image::color::any::convert_visitor<
				Dest
			>(),
			_color.get()
		);
}

#define SGE_INSTANTIATE_COLOR_CONVERT(\
	format_arg,\
	_\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::mizuiro_color<\
	sge::image::color::format_arg ## _format\
> \
sge::image::color::any::convert<\
	sge::image::color::format_arg ## _format\
>(\
	sge::image::color::any::object const &\
)

SGE_SRC_IMAGE_COLOR_INSTANTIATE_FORMAT(
	SGE_INSTANTIATE_COLOR_CONVERT,
	_
);

#undef SGE_INSTANTIATE_COLOR_CONVERT

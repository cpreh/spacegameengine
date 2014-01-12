/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/src/export_function_instantiation.hpp>
#include <sge/src/image/color/any/convert_visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


template<
	typename Dest
>
sge::image::mizuiro_color<
	Dest
> const
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
	format\
)\
template \
SGE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::mizuiro_color<\
	sge::image::color::format\
> const \
sge::image::color::any::convert<\
	sge::image::color::format\
>(\
	sge::image::color::any::object const &\
);

SGE_INSTANTIATE_COLOR_CONVERT(a8_format)
SGE_INSTANTIATE_COLOR_CONVERT(l8_format)
SGE_INSTANTIATE_COLOR_CONVERT(r32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(la8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgb8_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgr8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgba8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgbx8_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgra8_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgrx8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgb32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgr32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgba32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgra32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(srgb8_format)
SGE_INSTANTIATE_COLOR_CONVERT(srgba8_format)

#undef SGE_INSTANTIATE_COLOR_CONVERT

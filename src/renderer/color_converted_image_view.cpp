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


#include <sge/renderer/color_converted_image_view.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>

sge::renderer::image_view const
sge::renderer::color_converted_image_view(
	image_view const &view,
	color_format::type const fmt)
{
	switch(fmt) {
	case color_format::rgba8:
		return image_view(
			boost::gil::any_color_converted_view<
				renderer::rgba8_view>(
					view));
	case color_format::bgra8:
		return image_view(
			boost::gil::any_color_converted_view<
				renderer::bgra8_view>(
					view));
	case color_format::argb8:
		return image_view(
			boost::gil::any_color_converted_view<
				renderer::argb8_view>(
					view));
	case color_format::rgbaf32:
		return image_view(
			boost::gil::any_color_converted_view<
				renderer::rgba_f32_view>(
					view));
	default:
		throw exception(
			SGE_TEXT("Invalid color_format in color_converted_image_view!"));
	}
}

sge::renderer::const_image_view const
sge::renderer::color_converted_image_view(
	const_image_view const &view,
	color_format::type const fmt)
{
	// TODO:	
}


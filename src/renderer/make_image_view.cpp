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


#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/color.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <boost/cstdint.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <cstddef>

namespace
{

template<typename Pixel>
sge::renderer::image_view const
make_interleaved_view(
	unsigned char *data,
	sge::renderer::image_dim const &,
	std::size_t stride);

}

sge::renderer::image_view const
sge::renderer::make_image_view(
	unsigned char * const data,
	image_dim const &d,
	color_format::type const format)
{
	switch(format) {
	case color_format::rgba8:
		return make_interleaved_view<renderer::rgba8_pixel>(
			data,
			d,
			sizeof(boost::uint32_t));
	case color_format::argb8:
		return make_interleaved_view<renderer::argb8_pixel>(
			data,
			d,
			sizeof(boost::uint32_t));
	default:
		throw exception(
			SGE_TEXT("Invalid color_format!"));
	}
}

sge::renderer::const_image_view const
sge::renderer::make_image_view(
	unsigned char const * const data,
	image_dim const &d,
	color_format::type const format)
{
	return const_image_view(
		make_image_view(
			const_cast<unsigned char *>(data),
			d,
			format));
}

namespace
{

template<typename Pixel>
sge::renderer::image_view const
make_interleaved_view(
	unsigned char * const data,
	sge::renderer::image_dim const &d,
	std::size_t const stride)
{
	return sge::renderer::image_view(
		boost::gil::interleaved_view(
			d.w(),
			d.h(),
			reinterpret_cast<Pixel *>(
				data),
			d.w() * stride));
}

}

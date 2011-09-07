/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opencl/memory_object/image/sge_color_format_to_opencl.hpp>
#include <fcppt/assert/unreachable.hpp>

cl_image_format const
sge::opencl::memory_object::image::sge_color_format_to_opencl(
	sge::image::color::format::type const f)
{
	cl_image_format result;
	switch(f)
	{
		case sge::image::color::format::alpha8:
			result.image_channel_order = CL_A;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::gray8:
			result.image_channel_order = CL_INTENSITY;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::rgba8:
			result.image_channel_order = CL_RGBA;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::argb8:
			result.image_channel_order = CL_ARGB;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::xrgb8:
			FCPPT_ASSERT_UNREACHABLE;
		case sge::image::color::format::bgra8:
			result.image_channel_order = CL_BGRA;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::rgb8:
			result.image_channel_order = CL_RGB;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::rgba32f:
			result.image_channel_order = CL_RGB;
			result.image_channel_data_type = CL_FLOAT;
			break;
		case sge::image::color::format::argb32f:
			result.image_channel_order = CL_ARGB;
			result.image_channel_data_type = CL_FLOAT;
			break;
		case sge::image::color::format::bgra32f:
			result.image_channel_order = CL_BGRA;
			result.image_channel_data_type = CL_FLOAT;
			break;
		case sge::image::color::format::rgb32f:
			result.image_channel_order = CL_RGB;
			result.image_channel_data_type = CL_FLOAT;
			break;
		case sge::image::color::format::ag8:
			FCPPT_ASSERT_UNREACHABLE;
			break;
		case sge::image::color::format::ga8:
			result.image_channel_order = CL_RA;
			result.image_channel_data_type = CL_UNORM_INT8;
			break;
		case sge::image::color::format::size:
			break;
	}
	return result;
}

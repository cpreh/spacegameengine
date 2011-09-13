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


#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::image::color::format::type
sge::opencl::memory_object::image::opencl_color_format_to_sge(
	cl_image_format const &f)
{
	if(f.image_channel_order == CL_A && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::a8;

	if(f.image_channel_order == CL_INTENSITY && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::l8;

	// TODO: is this right?
	if(f.image_channel_order == CL_RA && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::la8;

	if(f.image_channel_order == CL_RGB && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::rgb8;

	if(f.image_channel_order == CL_RGBA && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::rgba8;

	// TODO: is rgbx == CL_RGBx?

	if(f.image_channel_order == CL_BGRA && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::bgra8;

	if(f.image_channel_order == CL_RGB && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::rgb32f;

	if(f.image_channel_order == CL_RGBA && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::rgba32f;

	if(f.image_channel_order == CL_BGRA && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::bgra32f;

	FCPPT_ASSERT_UNREACHABLE;
}

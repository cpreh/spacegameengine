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


#include <sge/image/color/format.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/memory_object/image/sge_color_format_to_opencl.hpp>
#include <fcppt/assert/unreachable.hpp>


namespace
{

cl_image_format
make_cl_image_format(
	cl_channel_order const _order,
	cl_channel_type const _type
)
{
	cl_image_format const ret = {
		_order,
		_type
	};

	return ret;
}

}

cl_image_format const
sge::opencl::memory_object::image::sge_color_format_to_opencl(
	sge::image::color::format::type const f)
{
	switch(f)
	{
		case sge::image::color::format::a8:
			return
				make_cl_image_format(
					CL_A,
					CL_UNORM_INT8);
		case sge::image::color::format::l8:
			return
				make_cl_image_format(
					CL_INTENSITY,
					CL_UNORM_INT8);
		case sge::image::color::format::r32f:
			return
				make_cl_image_format(
					CL_R,
					CL_FLOAT);
		case sge::image::color::format::la8:
			return
				make_cl_image_format(
					CL_RA,
					CL_UNORM_INT8);
		case sge::image::color::format::rgb8:
		case sge::image::color::format::bgr8:
			return
				make_cl_image_format(
					CL_RGB,
					CL_UNORM_INT8);
		case sge::image::color::format::rgba8:
		case sge::image::color::format::rgbx8: // TODO: map to CL_RGBx?
			return
				make_cl_image_format(
					CL_RGBA,
					CL_UNORM_INT8);
		case sge::image::color::format::bgra8:
		case sge::image::color::format::bgrx8: // TODO: would CL_RGBx be better?
			return
				make_cl_image_format(
					CL_BGRA,
					CL_UNORM_INT8);
		case sge::image::color::format::rgb32f:
		case sge::image::color::format::bgr32f:
			return
				make_cl_image_format(
					CL_RGB,
					CL_FLOAT);
		case sge::image::color::format::rgba32f:
		case sge::image::color::format::bgra32f:
			return
				make_cl_image_format(
					CL_RGBA,
					CL_FLOAT);
		case sge::image::color::format::size:
			break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::color::format
sge::opencl::memory_object::image::opencl_color_format_to_sge(
	cl_image_format const &f)
{
	if(f.image_channel_order == CL_A && f.image_channel_data_type == CL_UNORM_INT8)
	{
		return sge::image::color::format::a8;
	}

	if(f.image_channel_order == CL_INTENSITY && f.image_channel_data_type == CL_UNORM_INT8)
	{
		return sge::image::color::format::l8;
	}

	// TODO(philipp): is this right?
	if(f.image_channel_order == CL_RA && f.image_channel_data_type == CL_UNORM_INT8)
	{
		return sge::image::color::format::la8;
	}

	if(f.image_channel_order == CL_RGB && f.image_channel_data_type == CL_UNORM_INT8)
	{
		return sge::image::color::format::rgb8;
	}

	if(f.image_channel_order == CL_RGBA && f.image_channel_data_type == CL_UNORM_INT8)
	{
		return sge::image::color::format::rgba8;
	}

	// TODO(philipp): is rgbx == CL_RGBx?

	if(f.image_channel_order == CL_BGRA && f.image_channel_data_type == CL_UNORM_INT8)
	{
		return sge::image::color::format::bgra8;
	}

	if(f.image_channel_order == CL_RGB && f.image_channel_data_type == CL_FLOAT)
	{
		return sge::image::color::format::rgb32f;
	}

	if(f.image_channel_order == CL_RGBA && f.image_channel_data_type == CL_FLOAT)
	{
		return sge::image::color::format::rgba32f;
	}

	if(f.image_channel_order == CL_BGRA && f.image_channel_data_type == CL_FLOAT)
	{
		return sge::image::color::format::bgra32f;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

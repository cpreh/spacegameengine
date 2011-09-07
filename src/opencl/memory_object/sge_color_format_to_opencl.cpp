#include "sge_color_format_to_opencl.hpp"
#include <fcppt/assert/unreachable.hpp>

cl_image_format const
sge::opencl::memory_object::sge_color_format_to_opencl(
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

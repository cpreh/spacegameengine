#include "opencl_color_format_to_sge.hpp"
#include <fcppt/assert/unreachable.hpp>

sge::image::color::format::type
sge::opencl::memory_object::opencl_color_format_to_sge(
	cl_image_format const &f)
{
	if(f.image_channel_order == CL_A && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::alpha8;

	if(f.image_channel_order == CL_INTENSITY && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::gray8;

	if(f.image_channel_order == CL_RGBA && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::rgba8;

	if(f.image_channel_order == CL_ARGB && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::argb8;

	if(f.image_channel_order == CL_BGRA && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::bgra8;

	if(f.image_channel_order == CL_RGB && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::rgb8;

	if(f.image_channel_order == CL_RGBA && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::rgb32f;

	if(f.image_channel_order == CL_ARGB && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::argb32f;

	if(f.image_channel_order == CL_BGRA && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::bgra32f;

	if(f.image_channel_order == CL_RGB && f.image_channel_data_type == CL_FLOAT)
		return sge::image::color::format::rgb32f;

	if(f.image_channel_order == CL_RA && f.image_channel_data_type == CL_UNORM_INT8)
		return sge::image::color::format::ga8;

	FCPPT_ASSERT_UNREACHABLE;
}

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

cl_image_format
sge::opencl::memory_object::image::sge_color_format_to_opencl(
	sge::image::color::format const f)
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
		// CL doesn't seem to support sRGB directly
		case sge::image::color::format::srgb8:
		case sge::image::color::format::bgr8:
		case sge::image::color::format::sbgr8:
			return
				make_cl_image_format(
					CL_RGB,
					CL_UNORM_INT8);
		case sge::image::color::format::rgba8:
		// CL doesn't seem to support sRGB directly
		case sge::image::color::format::srgba8:
		case sge::image::color::format::rgbx8: // TODO: map to CL_RGBx?
			return
				make_cl_image_format(
					CL_RGBA,
					CL_UNORM_INT8);
		case sge::image::color::format::bgra8:
		case sge::image::color::format::sbgra8:
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
	}

	FCPPT_ASSERT_UNREACHABLE;
}

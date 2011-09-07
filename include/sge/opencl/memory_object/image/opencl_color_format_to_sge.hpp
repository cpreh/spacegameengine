#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_OPENCL_COLOR_FORMAT_TO_SGE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_OPENCL_COLOR_FORMAT_TO_SGE_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
sge::image::color::format::type
opencl_color_format_to_sge(
	cl_image_format const &);
}
}
}
}

#endif

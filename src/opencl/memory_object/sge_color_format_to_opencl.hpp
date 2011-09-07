#ifndef SGE_OPENCL_MEMORY_OBJECT_SGE_COLOR_FORMAT_TO_OPENCL_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_SGE_COLOR_FORMAT_TO_OPENCL_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/opencl/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
SGE_OPENCL_SYMBOL cl_image_format const
sge_color_format_to_opencl(
	sge::image::color::format::type);
}
}
}

#endif

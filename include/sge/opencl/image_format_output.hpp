#ifndef SGE_OPENCL_IMAGE_FORMAT_OUTPUT_HPP_INCLUDED
#define SGE_OPENCL_IMAGE_FORMAT_OUTPUT_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
SGE_OPENCL_SYMBOL void
image_format_output(
	std::ostream &,
	cl_image_format const &);
}
}

#endif

#ifndef SGE_OPENCL_IMAGE_FORMAT_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_IMAGE_FORMAT_SEQUENCE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
typedef
std::vector<cl_image_format>
image_format_sequence;
}
}

#endif

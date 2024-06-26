//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/exception.hpp>
#include <sge/opencl/memory_object/image/format_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <ostream>
#include <fcppt/config/external_end.hpp>

#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(constant) \
  case constant: \
    s << #constant; \
    break

void sge::opencl::memory_object::image::format_output(std::ostream &s, cl_image_format const &_if)
{
  switch (_if.image_channel_order)
  {
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_R);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_A);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_INTENSITY);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_LUMINANCE);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_RG);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_RA);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_RGB);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_RGBA);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_ARGB);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_BGRA);
    default:
      throw sge::opencl::exception{FCPPT_TEXT("Invalid image channel order.")};
  }

  s << " ";

  switch (_if.image_channel_data_type)
  {
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_SNORM_INT8);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_SNORM_INT16);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNORM_INT8);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNORM_INT16);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNORM_SHORT_565);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNORM_SHORT_555);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNORM_INT_101010);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_SIGNED_INT8);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_SIGNED_INT16);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_SIGNED_INT32);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNSIGNED_INT8);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNSIGNED_INT16);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_UNSIGNED_INT32);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_HALF_FLOAT);
    SGE_OPENCL_MEMORY_OBJECT_IMAGE_FORMAT_OUTPUT_HELPER(CL_FLOAT);
    default:
      throw sge::opencl::exception{FCPPT_TEXT("Invalid image channel data type.")};
  }
}

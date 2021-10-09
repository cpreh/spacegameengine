//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/memory_object/create_image_format.hpp>

cl_image_format
sge::opencl::memory_object::create_image_format(cl_channel_order const co, cl_channel_type const ct)
{
  cl_image_format result;
  result.image_channel_order = co;
  result.image_channel_data_type = ct;
  return result;
}

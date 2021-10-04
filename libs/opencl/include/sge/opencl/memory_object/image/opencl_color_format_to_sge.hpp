//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_OPENCL_COLOR_FORMAT_TO_SGE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_OPENCL_COLOR_FORMAT_TO_SGE_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/opencl/clinclude.hpp>

namespace sge::opencl::memory_object::image
{
sge::image::color::format
opencl_color_format_to_sge(
	cl_image_format const &);
}

#endif

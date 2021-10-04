//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_SGE_COLOR_FORMAT_TO_OPENCL_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_SGE_COLOR_FORMAT_TO_OPENCL_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/detail/symbol.hpp>


namespace sge::opencl::memory_object::image
{
SGE_OPENCL_DETAIL_SYMBOL cl_image_format
sge_color_format_to_opencl(
	sge::image::color::format);
}

#endif

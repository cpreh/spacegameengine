//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_READ_PLANAR_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_READ_PLANAR_HPP_INCLUDED

#include <sge/image2d/view/object_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/memory_object/image/planar_fwd.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
SGE_OPENCL_DETAIL_SYMBOL void
read_planar(
	opencl::command_queue::object &,
	memory_object::image::planar const &,
	sge::image2d::view::object const &,
	opencl::memory_object::rect const &);
}
}
}
}

#endif

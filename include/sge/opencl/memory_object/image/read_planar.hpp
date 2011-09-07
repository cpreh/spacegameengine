#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_READ_PLANAR_TEXTURE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_READ_PLANAR_TEXTURE_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/memory_object/image/planar_fwd.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/image2d/view/object_fwd.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
SGE_OPENCL_SYMBOL void
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

#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/memory_object/image/planar_fwd.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace command_queue
{
class scoped_planar_mapping
{
FCPPT_NONCOPYABLE(
	scoped_planar_mapping);
public:
	SGE_OPENCL_SYMBOL explicit
	scoped_planar_mapping(
		command_queue::object &,
		opencl::memory_object::image::planar &,
		cl_map_flags,
		opencl::memory_object::rect const &);

	SGE_OPENCL_SYMBOL void*
	ptr() const;

	SGE_OPENCL_SYMBOL std::size_t
	pitch() const;

	SGE_OPENCL_SYMBOL sge::image2d::view::object const
	view();

	SGE_OPENCL_SYMBOL ~scoped_planar_mapping();
private:
	command_queue::object &queue_;
	opencl::memory_object::rect rect_;
	sge::image::color::format::type sge_image_format_;
	cl_mem image_;
	void *ptr_;
	std::size_t pitch_;
};
}
}
}

#endif

#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/memory_object/planar_texture_fwd.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <fcppt/noncopyable.hpp>
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
	explicit
	scoped_planar_mapping(
		command_queue::object &,
		opencl::memory_object::planar_texture &,
		cl_map_flags,
		opencl::memory_object::rect const &);

	void*
	ptr() const;

	std::size_t
	pitch() const;

	~scoped_planar_mapping();
private:
	command_queue::object &queue_;
	cl_mem image_;
	void *ptr_;
	std::size_t pitch_;
};
}
}
}

#endif

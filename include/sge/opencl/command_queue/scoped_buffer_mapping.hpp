#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_BUFFER_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_BUFFER_MAPPING_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/memory_object/byte_offset.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/memory_object/buffer_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/clinclude.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opencl
{
namespace command_queue
{
class scoped_buffer_mapping
{
FCPPT_NONCOPYABLE(
	scoped_buffer_mapping);
public:
	SGE_OPENCL_SYMBOL explicit
	scoped_buffer_mapping(
		command_queue::object &,
		opencl::memory_object::buffer &,
		cl_map_flags,
		memory_object::byte_offset const &,
		memory_object::byte_size const &);

	SGE_OPENCL_SYMBOL void*
	ptr() const;

	SGE_OPENCL_SYMBOL ~scoped_buffer_mapping();
private:
	command_queue::object &queue_;
	cl_mem buffer_;
	void *ptr_;
};
}
}
}

#endif

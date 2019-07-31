//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_BUFFER_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_BUFFER_MAPPING_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/command_queue/map_flags_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/memory_object/buffer_fwd.hpp>
#include <sge/opencl/memory_object/byte_offset.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
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
	SGE_OPENCL_DETAIL_SYMBOL
	scoped_buffer_mapping(
		sge::opencl::command_queue::object &,
		sge::opencl::memory_object::buffer &,
		sge::opencl::command_queue::map_flags,
		sge::opencl::memory_object::byte_offset const &,
		sge::opencl::memory_object::byte_size const &,
		sge::opencl::event::sequence const &);

	SGE_OPENCL_DETAIL_SYMBOL void*
	ptr() const;

	SGE_OPENCL_DETAIL_SYMBOL ~scoped_buffer_mapping();
private:
	sge::opencl::command_queue::object &queue_;
	cl_mem buffer_;
	void *ptr_;
};
}
}
}

#endif

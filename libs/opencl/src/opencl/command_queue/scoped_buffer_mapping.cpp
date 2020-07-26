//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/map_flags_to_native.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/command_queue/scoped_buffer_mapping.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/event/flatten_sequence.hpp>
#include <sge/opencl/memory_object/buffer.hpp>
#include <sge/opencl/memory_object/buffer_ref.hpp>
#include <fcppt/text.hpp>


sge::opencl::command_queue::scoped_buffer_mapping::scoped_buffer_mapping(
	sge::opencl::command_queue::object_ref const _queue,
	sge::opencl::memory_object::buffer_ref const _buffer,
	sge::opencl::command_queue::map_flags const _flags,
	sge::opencl::memory_object::byte_offset const &_offset,
	sge::opencl::memory_object::byte_size const &_size,
	sge::opencl::event::sequence const &_events
)
:
	queue_(
		_queue
	),
	buffer_(
		_buffer.get().impl()
	),
	ptr_(
		nullptr
	)
{
	cl_int error_code{};

	ptr_ =
		clEnqueueMapBuffer(
			_queue.get().impl(),
			buffer_,
			// Blocking: yes
			CL_TRUE,
			sge::opencl::command_queue::map_flags_to_native(
				_flags),
			_offset.get(),
			_size.get(),
			static_cast<cl_uint>(
				_events.size()),
			_events.empty()
			?
				nullptr
			:
				sge::opencl::impl::event::flatten_sequence(
					_events).data(),
			// result event
			nullptr,
			&error_code);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueMapBuffer"));
}

void*
sge::opencl::command_queue::scoped_buffer_mapping::ptr() const
{
	return ptr_;
}

sge::opencl::command_queue::scoped_buffer_mapping::~scoped_buffer_mapping()
{
	if(
		ptr_
		==
		nullptr
	)
	{
		return;
	}

	cl_int const error_code =
		clEnqueueUnmapMemObject(
			queue_.get().impl(),
			buffer_,
			this->ptr(),
			0,
			nullptr,
			nullptr);

	opencl::impl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueUnmapMemObject"));
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opencl/command_queue/map_flags_to_native.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/scoped_buffer_mapping.hpp>
#include <sge/opencl/memory_object/buffer.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>


sge::opencl::command_queue::scoped_buffer_mapping::scoped_buffer_mapping(
	sge::opencl::command_queue::object &_queue,
	sge::opencl::memory_object::buffer &_buffer,
	sge::opencl::command_queue::map_flags::type const _flags,
	sge::opencl::memory_object::byte_offset const &_offset,
	sge::opencl::memory_object::byte_size const &_size,
	sge::opencl::command_queue::event_sequence const &_events)
:
	queue_(
		_queue),
	buffer_(
		_buffer.impl()),
	ptr_(
		0)
{
	cl_int error_code;

	ptr_ =
		clEnqueueMapBuffer(
			_queue.impl(),
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
				0
			:
				_events.data(),
			// result event
			0,
			&error_code);

	opencl::handle_error(
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
	if(!ptr_)
		return;

	cl_int const error_code =
		clEnqueueUnmapMemObject(
			queue_.impl(),
			buffer_,
			this->ptr(),
			0,
			0,
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueUnmapMemObject"));
}

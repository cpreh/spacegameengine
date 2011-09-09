/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../handle_error.hpp"
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>

template<std::size_t N>
void
sge::opencl::command_queue::enqueue_kernel(
	command_queue::object &_queue,
	kernel::object &_kernel,
	fcppt::container::array<std::size_t,N> const &global_dim,
	fcppt::container::array<std::size_t,N> const &work_dim)
{
	cl_int const error_code =
		clEnqueueNDRangeKernel(
			_queue.impl(),
			_kernel.impl(),
			static_cast<cl_uint>(
				N),
			0, // global work offset (not implemented in 1.1)
			global_dim.data(),
			work_dim.data(),
			0,
			0,
			0);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clEnqueueNDRangeKernel"));
}

#define SGE_OPENCL_COMMAND_QUEUE_INSTANTIATE_ENQUEUE_KERNEL(\
	arity\
)\
template FCPPT_EXPORT_SYMBOL \
void sge::opencl::command_queue::enqueue_kernel<\
	arity\
>( \
	command_queue::object &_queue, \
	kernel::object &, \
	fcppt::container::array<std::size_t,arity> const &, \
	fcppt::container::array<std::size_t,arity> const &);

SGE_OPENCL_COMMAND_QUEUE_INSTANTIATE_ENQUEUE_KERNEL(1)
SGE_OPENCL_COMMAND_QUEUE_INSTANTIATE_ENQUEUE_KERNEL(2)
SGE_OPENCL_COMMAND_QUEUE_INSTANTIATE_ENQUEUE_KERNEL(3)

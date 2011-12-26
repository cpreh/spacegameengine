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


#include <sge/exception.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/container/array.hpp>

namespace
{
template<std::size_t N>
fcppt::string
output_dimension(
	fcppt::container::array<std::size_t,N> const &a)
{
	fcppt::io::ostringstream ss;

	ss << FCPPT_TEXT("[");

	for(std::size_t i = 0; i < a.size(); ++i)
		if(i == static_cast<std::size_t>(a.size()-1))
			ss << a[i];
		else
			ss << a[i] << FCPPT_TEXT(",");

	ss << FCPPT_TEXT("]");

	return ss.str();
}
}

template<std::size_t N>
void
sge::opencl::command_queue::enqueue_kernel(
	command_queue::object &_queue,
	kernel::object &_kernel,
	fcppt::container::array<std::size_t,N> const &global_dim,
	fcppt::container::array<std::size_t,N> const &work_dim)
{
	for(std::size_t i = 0; i < N; ++i)
		if(global_dim[i] == 0 || work_dim[i] == 0)
			throw sge::exception(
				FCPPT_TEXT("Neither global nor work dimensions can be zero in any component"));

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

	if(error_code == CL_INVALID_WORK_GROUP_SIZE)
	{
		throw
			sge::exception(
				FCPPT_TEXT("Error enqueuing kernel \"")+
				fcppt::from_std_string(
					_kernel.name())+
				FCPPT_TEXT("\": workgroup size invalid. The global dimension is ")+
				output_dimension(
					global_dim)+
				FCPPT_TEXT(", the workgroup dimension is ")+
				output_dimension(
					work_dim));
	}

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

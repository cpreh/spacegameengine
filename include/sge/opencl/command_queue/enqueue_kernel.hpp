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


#ifndef SGE_OPENCL_COMMAND_QUEUE_ENQUEUE_KERNEL_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_ENQUEUE_KERNEL_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/command_queue/event_sequence.hpp>
#include <sge/opencl/command_queue/global_dim1.hpp>
#include <sge/opencl/command_queue/global_dim2.hpp>
#include <sge/opencl/command_queue/global_dim3.hpp>
#include <sge/opencl/command_queue/local_dim1.hpp>
#include <sge/opencl/command_queue/local_dim2.hpp>
#include <sge/opencl/command_queue/local_dim3.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{
SGE_OPENCL_SYMBOL
cl_event
enqueue_kernel(
	sge::opencl::command_queue::object &,
	sge::opencl::kernel::object &,
	sge::opencl::command_queue::global_dim1 const &,
	sge::opencl::command_queue::local_dim1 const &,
	sge::opencl::command_queue::event_sequence const &);

SGE_OPENCL_SYMBOL
cl_event
enqueue_kernel(
	sge::opencl::command_queue::object &,
	sge::opencl::kernel::object &,
	sge::opencl::command_queue::global_dim2 const &,
	sge::opencl::command_queue::local_dim2 const &,
	sge::opencl::command_queue::event_sequence const &);

SGE_OPENCL_SYMBOL
cl_event
enqueue_kernel(
	sge::opencl::command_queue::object &,
	sge::opencl::kernel::object &,
	sge::opencl::command_queue::global_dim3 const &,
	sge::opencl::command_queue::local_dim3 const &,
	sge::opencl::command_queue::event_sequence const &);

SGE_OPENCL_SYMBOL
cl_event
enqueue_kernel(
	sge::opencl::command_queue::object &,
	sge::opencl::kernel::object &,
	sge::opencl::command_queue::global_dim1 const &,
	sge::opencl::command_queue::event_sequence const &);

SGE_OPENCL_SYMBOL
cl_event
enqueue_kernel(
	sge::opencl::command_queue::object &,
	sge::opencl::kernel::object &,
	sge::opencl::command_queue::global_dim2 const &,
	sge::opencl::command_queue::event_sequence const &);

SGE_OPENCL_SYMBOL
cl_event
enqueue_kernel(
	sge::opencl::command_queue::object &,
	sge::opencl::kernel::object &,
	sge::opencl::command_queue::global_dim3 const &,
	sge::opencl::command_queue::event_sequence const &);
}
}
}

#endif

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


#ifndef SGE_OPENCL_COMMAND_QUEUE_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_OBJECT_HPP_INCLUDED

#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/array_decl.hpp>
#include <cstddef>

namespace sge
{
namespace opencl
{
namespace command_queue
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		opencl::device::object &,
		opencl::context::object &,
		command_queue::execution_mode::type,
		command_queue::profiling_mode::type);

	SGE_OPENCL_SYMBOL cl_command_queue
	impl() const;

	template<std::size_t N>
	SGE_OPENCL_SYMBOL void
	enqueue(
		opencl::kernel::object &,
		fcppt::container::array<std::size_t,N> const &global_dim,
		fcppt::container::array<std::size_t,N> const &work_dim);

	SGE_OPENCL_SYMBOL ~object();
private:
	cl_command_queue queue_;
};
}
}
}

#endif

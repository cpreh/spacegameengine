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


#ifndef SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/kernel/argument_index.hpp>
#include <sge/opencl/kernel/name.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/kernel/numeric_type.hpp>
#include <sge/opencl/memory_object/base_fwd.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>


namespace sge
{
namespace opencl
{
namespace kernel
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		program::object &,
		kernel::name const &);

	SGE_OPENCL_SYMBOL void
	argument(
		kernel::argument_index const &,
		memory_object::base &);

	SGE_OPENCL_SYMBOL void
	argument(
		kernel::argument_index const &,
		kernel::numeric_type const &);

	SGE_OPENCL_SYMBOL void
	argument(
		kernel::argument_index const &,
		unsigned char const *,
		memory_object::byte_size const &);

	SGE_OPENCL_SYMBOL std::size_t
	work_group_size(
		opencl::device::object &) const;

	SGE_OPENCL_SYMBOL cl_kernel
	impl();

	SGE_OPENCL_SYMBOL ~object();
private:
	cl_kernel kernel_;
	cl_uint argument_count_;
};
}
}
}

#endif

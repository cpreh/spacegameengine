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


#ifndef SGE_OPENCL_KERNEL_LOCAL_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_LOCAL_BUFFER_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>


namespace sge
{
namespace opencl
{
namespace kernel
{
class local_buffer
{
public:
	SGE_OPENCL_SYMBOL explicit
	local_buffer(
		memory_object::byte_size const &);

	SGE_OPENCL_SYMBOL memory_object::byte_size::value_type
	byte_size() const;
private:
	memory_object::byte_size byte_size_;
};
}
}
}

#endif

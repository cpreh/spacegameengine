//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/kernel/local_buffer.hpp>

sge::opencl::kernel::local_buffer::local_buffer(
	memory_object::byte_size const &_byte_size)
:
	byte_size_(
		_byte_size)
{
}

sge::opencl::memory_object::byte_size::value_type
sge::opencl::kernel::local_buffer::byte_size() const
{
	return byte_size_.get();
}

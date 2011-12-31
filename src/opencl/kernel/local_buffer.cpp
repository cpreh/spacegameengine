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

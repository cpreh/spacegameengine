#ifndef SGE_OPENCL_KERNEL_LOCAL_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_LOCAL_BUFFER_HPP_INCLUDED

#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/symbol.hpp>

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

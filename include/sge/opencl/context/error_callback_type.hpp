#ifndef SGE_OPENCL_CONTEXT_ERROR_CALLBACK_TYPE_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_ERROR_CALLBACK_TYPE_HPP_INCLUDED

#include <sge/opencl/error_information_string.hpp>
#include <sge/opencl/binary_error_data.hpp>

namespace sge
{
namespace opencl
{
namespace context
{
typedef
void
error_callback_type(
	opencl::error_information_string const &,
	opencl::binary_error_data const &);
}
}
}

#endif

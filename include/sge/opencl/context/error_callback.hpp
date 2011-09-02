#ifndef SGE_OPENCL_CONTEXT_ERROR_CALLBACK_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_ERROR_CALLBACK_HPP_INCLUDED

#include <sge/opencl/context/error_callback_type.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace opencl
{
namespace context
{
typedef
fcppt::function::object<context::error_callback_type>
error_callback;
}
}
}

#endif

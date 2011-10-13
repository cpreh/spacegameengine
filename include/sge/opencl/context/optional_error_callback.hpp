#ifndef SGE_OPENCL_CONTEXT_OPTIONAL_ERROR_CALLBACK_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_OPTIONAL_ERROR_CALLBACK_HPP_INCLUDED

#include <sge/opencl/context/error_callback.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace opencl
{
namespace context
{
typedef
fcppt::optional<context::error_callback>
optional_error_callback;
}
}
}

#endif

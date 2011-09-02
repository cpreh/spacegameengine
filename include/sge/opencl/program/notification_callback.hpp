#ifndef SGE_OPENCL_PROGRAM_NOTIFICATION_CALLBACK_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_NOTIFICATION_CALLBACK_HPP_INCLUDED

#include <sge/opencl/program/notification_callback_type.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace opencl
{
namespace program
{
typedef
fcppt::function::object<program::notification_callback_type>
notification_callback;
}
}
}

#endif

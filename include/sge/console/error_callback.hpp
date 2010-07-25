#ifndef SGE_CONSOLE_ERROR_CALLBACK_HPP_INCLUDED
#define SGE_CONSOLE_ERROR_CALLBACK_HPP_INCLUDED

#include <sge/console/error_callback_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace console
{
typedef
fcppt::function::object
<
	error_callback_fn
>
error_callback;
}
}

#endif

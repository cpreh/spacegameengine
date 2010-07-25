#ifndef SGE_CONSOLE_MESSAGE_CALLBACK_HPP_INCLUDED
#define SGE_CONSOLE_MESSAGE_CALLBACK_HPP_INCLUDED

#include <sge/console/message_callback_fn.hpp>
#include <fcppt/function/object.hpp>

namespace sge
{
namespace console
{
typedef
fcppt::function::object
<
	message_callback_fn
>
message_callback;
}
}

#endif

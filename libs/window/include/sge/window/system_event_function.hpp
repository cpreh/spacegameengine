//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_SYSTEM_EVENT_FUNCTION_HPP_INCLUDED
#define SGE_WINDOW_SYSTEM_EVENT_FUNCTION_HPP_INCLUDED

#include <sge/window/system_event_function_type.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace window
{

typedef
fcppt::function<
	sge::window::system_event_function_type
>
system_event_function;

}
}

#endif

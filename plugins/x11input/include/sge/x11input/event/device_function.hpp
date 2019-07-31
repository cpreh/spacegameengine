//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_DEVICE_FUNCTION_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_DEVICE_FUNCTION_HPP_INCLUDED

#include <sge/x11input/event/device_function_type.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

typedef
fcppt::function<
	sge::x11input::event::device_function_type
>
device_function;

}
}
}

#endif

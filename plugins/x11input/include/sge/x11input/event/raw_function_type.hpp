//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_RAW_FUNCTION_TYPE_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_RAW_FUNCTION_TYPE_HPP_INCLUDED

#include <awl/event/container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

using
raw_function_type
=
awl::event::container (
	XIRawEvent const &
);

}
}
}

#endif

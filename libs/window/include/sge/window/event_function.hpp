//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_EVENT_FUNCTION_HPP_INCLUDED
#define SGE_WINDOW_EVENT_FUNCTION_HPP_INCLUDED

#include <sge/window/event_function_type.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace window
{

using
event_function
=
fcppt::function<
	sge::window::event_function_type
>;

}
}

#endif

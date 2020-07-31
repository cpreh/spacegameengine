//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_TYPE_CONTAINER_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_TYPE_CONTAINER_HPP_INCLUDED

#include <sge/x11input/event/type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

using
type_container
=
std::vector<
	sge::x11input::event::type
>;

}
}
}

#endif

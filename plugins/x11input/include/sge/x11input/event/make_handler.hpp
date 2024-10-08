//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_EVENT_MAKE_HANDLER_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_MAKE_HANDLER_HPP_INCLUDED

#include <sge/x11input/event/concrete_handler.hpp>
#include <sge/x11input/event/handler.hpp>
#include <sge/x11input/event/static_type.hpp>
#include <sge/x11input/event/type.hpp>
#include <awl/backends/x11/system/event/generic.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::event
{

template <typename Type, typename Event>
std::pair<sge::x11input::event::type, sge::x11input::event::handler>
make_handler(sge::x11input::event::concrete_handler<Event> _function)
{
  return std::make_pair(
      sge::x11input::event::type{Type::value},
      sge::x11input::event::handler{
          [func = std::move(_function)](awl::backends::x11::system::event::generic const &_event)
          {
            using event_type = sge::x11input::event::static_type<Type>;

            static_assert(std::is_same_v<event_type, Event>, "Event types do not match");

            return func(*fcppt::cast::from_void_ptr<Event const *>(_event.data()));
          }});
}

}

#endif

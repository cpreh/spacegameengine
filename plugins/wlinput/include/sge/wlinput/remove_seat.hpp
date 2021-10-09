//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_REMOVE_SEAT_HPP_INCLUDED
#define SGE_WLINPUT_REMOVE_SEAT_HPP_INCLUDED

#include <sge/wlinput/map.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/caps_field.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::wlinput
{

template <
    awl::backends::wayland::system::seat::caps Caps,
    typename BasePtr,
    typename RemoveEvent,
    typename Object>
awl::event::optional_base_unique_ptr remove_seat(
    sge::wlinput::map<Object> &_map, awl::backends::wayland::system::seat::object const &_seat)
{
  using object_map = sge::wlinput::map<Object>;

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

  auto const make_event(
      [&_map, &_seat]
      {
        return fcppt::optional::map(
            fcppt::container::find_opt_iterator(_map, _seat.name()),
            [&_map](typename object_map::iterator const _iterator)
            {
              awl::event::base_unique_ptr event{fcppt::unique_ptr_to_base<awl::event::base>(
                  fcppt::make_unique_ptr<RemoveEvent>(BasePtr{_iterator->second}))};

              _map.erase(_iterator);

              return event;
            });
      });

  FCPPT_PP_POP_WARNING

  return fcppt::optional::join(fcppt::optional::make_if(_seat.caps() & Caps, make_event));
}

}

#endif

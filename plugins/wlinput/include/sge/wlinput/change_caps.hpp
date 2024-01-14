//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_CHANGE_CAPS_HPP_INCLUDED
#define SGE_WLINPUT_CHANGE_CAPS_HPP_INCLUDED

#include <sge/input/exception.hpp>
#include <sge/wlinput/create_function.hpp>
#include <sge/wlinput/map.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/caps_field.hpp> // IWYU pragma: keep
#include <awl/backends/wayland/system/seat/object.hpp> // IWYU pragma: keep
#include <awl/backends/wayland/system/seat/object_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput
{

template <
    awl::backends::wayland::system::seat::caps Caps,
    typename BasePtr,
    typename Discover,
    typename Remove,
    typename Object>
awl::event::optional_base_unique_ptr change_caps(
    sge::wlinput::create_function<Object> const &_create_function,
    fcppt::reference<sge::wlinput::map<Object>> const _map,
    awl::backends::wayland::system::seat::object_ref const _seat)
{
  using object_map = sge::wlinput::map<Object>;

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

  auto const add_cap(
      [&_create_function, &_map, &_seat]() -> awl::event::optional_base_unique_ptr
      {
        return fcppt::optional::make_if(
            _map.get().count(_seat.get().name()) == 0U,
            [&_create_function, &_map, &_seat]
            {
              std::pair<typename object_map::iterator, bool> const result{
                  _map.get().insert(std::make_pair(
                      _seat.get().name(), _create_function(fcppt::make_ref(_seat.get().get()))))};

              if (fcppt::not_(result.second))
              {
                throw sge::input::exception{FCPPT_TEXT("Double insert in wlinput!")};
              }

              return fcppt::unique_ptr_to_base<awl::event::base>(
                  fcppt::make_unique_ptr<Discover>(BasePtr{result.first->second}));
            });
      });

  auto const remove_cap(
      [&_map, &_seat]() -> awl::event::optional_base_unique_ptr
      {
        return fcppt::optional::map(
            fcppt::container::find_opt_iterator(_map.get(), _seat.get().name()),
            [&_map](typename object_map::iterator const _iterator)
            {
              awl::event::base_unique_ptr result{fcppt::unique_ptr_to_base<awl::event::base>(
                  fcppt::make_unique_ptr<Remove>(BasePtr{_iterator->second}))};

              _map.get().erase(_iterator);

              return result;
            });
      });

  FCPPT_PP_POP_WARNING

  return _seat.get().caps() & Caps ? add_cap() : remove_cap();
}

}

#endif

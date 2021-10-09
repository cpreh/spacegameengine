//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_INITIAL_OBJECTS_HPP_INCLUDED
#define SGE_WLINPUT_INITIAL_OBJECTS_HPP_INCLUDED

#include <sge/wlinput/create_function.hpp>
#include <sge/wlinput/map.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/backends/wayland/system/seat/set.hpp>
#include <awl/backends/wayland/system/seat/shared_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::wlinput
{

template <typename Type, awl::backends::wayland::system::seat::caps Caps>
sge::wlinput::map<Type> initial_objects(
    sge::wlinput::create_function<Type> const &_create_function,
    awl::backends::wayland::system::seat::set const &_seats)
{
  using result_type = sge::wlinput::map<Type>;

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

  return fcppt::algorithm::map_optional<result_type>(
      _seats,
      [&_create_function](awl::backends::wayland::system::seat::shared_ptr const &_seat)
      {
        return fcppt::optional::make_if(
            _seat->caps() & Caps,
            [&_create_function, &_seat]
            {
              using value_type = typename result_type::value_type;

              return value_type{_seat->name(), _create_function(fcppt::make_ref(_seat->get()))};
            });
      });

  FCPPT_PP_POP_WARNING
}

}

#endif

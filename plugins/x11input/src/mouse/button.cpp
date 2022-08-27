//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/mouse/button.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

fcppt::optional::object<sge::input::mouse::button> sge::x11input::mouse::button(
    XIDeviceEvent const &_event, sge::input::mouse::button_info_container const &_info)
{
  sge::input::mouse::button_id const id{fcppt::cast::to_unsigned(_event.detail - 1)};

  return fcppt::optional::bind(
      _info[id],
      [&_event, id](fcppt::reference<sge::input::mouse::button_info const> const _button)
      {
        return fcppt::optional::make_if(
            _event.detail > 0, // TODO(philipp): why?
            [_button, id]
            {
              return sge::input::mouse::button{_button->code(), id};
            });
      });
}

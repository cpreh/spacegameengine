//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/device/info/string_from_atom.hpp>
#include <sge/x11input/mouse/button_code.hpp>
#include <sge/x11input/mouse/button_infos.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::mouse::button_info_container::vector sge::x11input::mouse::button_infos(
    XIButtonClassInfo const &_info, awl::backends::x11::display &_display)
{
  return fcppt::algorithm::map<sge::input::mouse::button_info_container::vector>(
      fcppt::make_int_range_count(_info.num_buttons),
      [&_info, &_display](int const _button_index)
      {
        fcppt::optional_string const name(sge::x11input::device::info::string_from_atom(
            _display,
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            _info.labels[_button_index]));

        return sge::input::mouse::button_info(
            sge::x11input::mouse::button_code(name),
            // TODO(philipp)
            fcppt::optional_string{name});
      });
}

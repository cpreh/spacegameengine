//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/device/info/class_maybe.hpp>
#include <sge/x11input/mouse/button_infos.hpp>
#include <sge/x11input/mouse/make_button_infos.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

sge::input::mouse::button_info_container sge::x11input::mouse::make_button_infos(
    awl::backends::x11::display &_display, XIDeviceInfo const &_info)
{
  return sge::input::mouse::button_info_container(fcppt::optional::to_exception(
      fcppt::algorithm::find_by_opt<sge::input::mouse::button_info_container::vector>(
          fcppt::make_int_range_count(_info.num_classes),
          [&_display, &_info](int const _index)
          {
            return fcppt::optional::map(
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                sge::x11input::device::info::class_maybe<XIButtonClassInfo>(*_info.classes[_index]),
                [&_display](fcppt::reference<XIButtonClassInfo const> const _button_class)
                { return sge::x11input::mouse::button_infos(_button_class.get(), _display); });
          }),
      [] { return sge::input::exception{FCPPT_TEXT("No button class found")}; }));
}

FCPPT_PP_POP_WARNING

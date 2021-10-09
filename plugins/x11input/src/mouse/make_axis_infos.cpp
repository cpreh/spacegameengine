//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/x11input/device/info/class_maybe.hpp>
#include <sge/x11input/mouse/axis_info.hpp>
#include <sge/x11input/mouse/make_axis_infos.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::mouse::axis_info_container sge::x11input::mouse::make_axis_infos(
    awl::backends::x11::display &_display, XIDeviceInfo const &_info)
{
  return sge::input::mouse::axis_info_container(
      fcppt::algorithm::map_optional<sge::input::mouse::axis_info_container::vector>(
          fcppt::make_int_range_count(_info.num_classes),
          [&_display, &_info](int const _index)
          {
            return fcppt::optional::bind(
                sge::x11input::device::info::class_maybe<XIValuatorClassInfo>(
                    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    *_info.classes[_index]),
                [&_display](fcppt::reference<XIValuatorClassInfo const> const _valuator_class)
                {
                  using result_type = fcppt::optional::object<sge::input::mouse::axis_info>;

                  return _valuator_class.get().mode == XIModeRelative
                             ? result_type(
                                   sge::x11input::mouse::axis_info(_valuator_class.get(), _display))
                             : result_type();
                });
          }));
}

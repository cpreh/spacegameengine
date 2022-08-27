//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_id.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/mouse/axis.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/optional/map.hpp>

fcppt::optional::object<sge::input::mouse::axis> sge::x11input::mouse::axis(
    sge::x11input::device::valuator::index const _index,
    sge::input::mouse::axis_info_container const &_info)
{
  auto const id{
      fcppt::strong_typedef_construct_cast<sge::input::mouse::axis_id, fcppt::cast::size_fun>(
          _index.get())};

  return fcppt::optional::map(
      _info[id],
      [id](fcppt::reference<sge::input::mouse::axis_info const> const _axis) {
        return sge::input::mouse::axis{_axis->code(), id};
      });
}

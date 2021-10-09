//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/info/id.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_id.hpp>
#include <sge/sdlinput/mouse/make_axis.hpp>
#include <fcppt/cast/enum_to_int.hpp>

sge::input::mouse::axis sge::sdlinput::mouse::make_axis(sge::input::mouse::axis_code const _code)
{
  return sge::input::mouse::axis{
      _code, sge::input::mouse::axis_id{fcppt::cast::enum_to_int<sge::input::info::id>(_code)}};
}

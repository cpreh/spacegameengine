//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_value.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::mouse::event::axis::axis(
    sge::input::mouse::shared_ptr _mouse,
    sge::input::mouse::axis const &_axis,
    sge::input::mouse::axis_value const _value)
    : sge::input::mouse::event::base{std::move(_mouse)}, axis_{_axis}, value_{_value}
{
}

sge::input::mouse::event::axis::~axis() = default;

sge::input::mouse::axis const &sge::input::mouse::event::axis::get() const { return axis_; }

sge::input::mouse::axis_code sge::input::mouse::event::axis::code() const { return axis_.code(); }

sge::input::mouse::axis_value sge::input::mouse::event::axis::value() const { return value_; }

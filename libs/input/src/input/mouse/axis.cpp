//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_id.hpp>

sge::input::mouse::axis::axis(
    sge::input::mouse::axis_code const _code, sge::input::mouse::axis_id const _id)
    : code_{_code}, id_{_id}
{
}

sge::input::mouse::axis_code sge::input::mouse::axis::code() const { return code_; }

sge::input::mouse::axis_id sge::input::mouse::axis::id() const { return id_; }

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_CURSOR_POSITION_FWD_HPP_INCLUDED
#define SGE_INPUT_CURSOR_POSITION_FWD_HPP_INCLUDED

#include <sge/input/cursor/position_unit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>

namespace sge::input::cursor
{

using position = fcppt::math::vector::static_<sge::input::cursor::position_unit, 2>;

}

#endif

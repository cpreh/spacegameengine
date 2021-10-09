//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_FF_OPTIONAL_TRIGGER_FWD_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_OPTIONAL_TRIGGER_FWD_HPP_INCLUDED

#include <sge/input/joypad/ff/trigger_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::input::joypad::ff
{

using optional_trigger = fcppt::optional::object<sge::input::joypad::ff::trigger>;

}

#endif

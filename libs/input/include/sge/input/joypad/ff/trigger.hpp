//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_FF_TRIGGER_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_TRIGGER_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/ff/trigger_cooldown.hpp>
#include <sge/input/joypad/ff/trigger_fwd.hpp> // IWYU pragma: keep

namespace sge::input::joypad::ff
{

class trigger
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  trigger(sge::input::joypad::button_id, sge::input::joypad::ff::trigger_cooldown);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::button_id button() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::trigger_cooldown cooldown() const;

private:
  sge::input::joypad::button_id button_;

  sge::input::joypad::ff::trigger_cooldown cooldown_;
};

}

#endif

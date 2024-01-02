//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_FF_PARAMETERS_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_PARAMETERS_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/delay.hpp>
#include <sge/input/joypad/ff/direction.hpp>
#include <sge/input/joypad/ff/optional_duration.hpp>
#include <sge/input/joypad/ff/optional_trigger.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp> // IWYU pragma: keep
#include <sge/input/joypad/ff/variant.hpp>

namespace sge::input::joypad::ff
{

class parameters
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  parameters(
      sge::input::joypad::ff::direction,
      sge::input::joypad::ff::optional_trigger const &,
      sge::input::joypad::ff::optional_duration const &,
      sge::input::joypad::ff::delay,
      sge::input::joypad::ff::variant const &);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::direction direction() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::optional_trigger const &
  trigger() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::optional_duration const &
  duration() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::delay delay() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::variant const &variant() const;

private:
  sge::input::joypad::ff::direction direction_;

  sge::input::joypad::ff::optional_trigger trigger_;

  sge::input::joypad::ff::optional_duration duration_;

  sge::input::joypad::ff::delay delay_;

  sge::input::joypad::ff::variant variant_;
};

}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_FF_CONDITION_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_CONDITION_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/condition_fwd.hpp> // IWYU pragma: keep
#include <sge/input/joypad/ff/condition_type.hpp>
#include <sge/input/joypad/ff/deadband_center.hpp>
#include <sge/input/joypad/ff/deadband_size.hpp>
#include <sge/input/joypad/ff/left_coefficient.hpp>
#include <sge/input/joypad/ff/left_saturation.hpp>
#include <sge/input/joypad/ff/right_coefficient.hpp>
#include <sge/input/joypad/ff/right_saturation.hpp>

namespace sge::input::joypad::ff
{

class condition
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  condition(
      sge::input::joypad::ff::condition_type,
      sge::input::joypad::ff::left_coefficient,
      sge::input::joypad::ff::right_coefficient,
      sge::input::joypad::ff::left_saturation,
      sge::input::joypad::ff::right_saturation,
      sge::input::joypad::ff::deadband_center,
      sge::input::joypad::ff::deadband_size);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::condition_type type() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::left_coefficient
  left_coefficient() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::right_coefficient
  right_coefficient() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::left_saturation
  left_saturation() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::right_saturation
  right_saturation() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::deadband_center
  deadband_center() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::deadband_size deadband_size() const;

private:
  sge::input::joypad::ff::condition_type type_;

  sge::input::joypad::ff::left_coefficient left_coefficient_;

  sge::input::joypad::ff::right_coefficient right_coefficient_;

  sge::input::joypad::ff::left_saturation left_saturation_;

  sge::input::joypad::ff::right_saturation right_saturation_;

  sge::input::joypad::ff::deadband_center deadband_center_;

  sge::input::joypad::ff::deadband_size deadband_size_;
};

}

#endif

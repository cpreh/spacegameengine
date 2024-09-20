//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_FF_TYPE_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_TYPE_HPP_INCLUDED

#include <sge/input/joypad/ff/type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::input::joypad::ff
{

enum class type : std::uint8_t
{
  constant,
  spring,
  friction,
  damper,
  inertia,
  ramp,
  square,
  sine,
  saw_up,
  saw_down,
  custom
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::input::joypad::ff::type::custom);

#endif

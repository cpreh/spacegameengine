//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_RELATIVE_AXIS_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_RELATIVE_AXIS_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/relative_axis_fwd.hpp> // IWYU pragma: keep
#include <sge/input/joypad/relative_axis_id.hpp>

namespace sge::input::joypad
{

class relative_axis
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  relative_axis(sge::input::joypad::axis_code, sge::input::joypad::relative_axis_id);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::axis_code code() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::relative_axis_id id() const;

private:
  sge::input::joypad::axis_code code_;

  sge::input::joypad::relative_axis_id id_;
};

}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_ABSOLUTE_AXIS_INFO_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_ABSOLUTE_AXIS_INFO_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/absolute_axis_info_fwd.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <fcppt/optional_string.hpp>

namespace sge::input::joypad
{

class absolute_axis_info
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  absolute_axis_info(
      sge::input::joypad::axis_code,
      fcppt::optional_string &&,
      sge::input::joypad::axis_min,
      sge::input::joypad::axis_max);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::axis_code code() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL fcppt::optional_string const &name() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::axis_min min() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::axis_max max() const;

private:
  sge::input::joypad::axis_code code_;

  fcppt::optional_string name_;

  sge::input::joypad::axis_min min_;

  sge::input::joypad::axis_max max_;
};

}

#endif

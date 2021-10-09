//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_EVENT_ABSOLUTE_AXIS_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_EVENT_ABSOLUTE_AXIS_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis_fwd.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::input::joypad::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL absolute_axis : public sge::input::joypad::event::base
{
  FCPPT_NONMOVABLE(absolute_axis);

public:
  SGE_INPUT_DETAIL_SYMBOL
  absolute_axis(
      sge::input::joypad::shared_ptr,
      sge::input::joypad::absolute_axis const &,
      sge::input::joypad::axis_value);

  SGE_INPUT_DETAIL_SYMBOL
  ~absolute_axis() override;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::absolute_axis const &axis() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::axis_value value() const;

private:
  sge::input::joypad::absolute_axis const axis_;

  sge::input::joypad::axis_value const axis_value_;
};

}

#endif

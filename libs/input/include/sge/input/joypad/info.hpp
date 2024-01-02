//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_INFO_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_INFO_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/info/unique_id.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info_fwd.hpp> // IWYU pragma: keep
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/ff/type_field.hpp>

namespace sge::input::joypad
{

class info
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  info(
      sge::input::joypad::absolute_axis_info_container &&,
      sge::input::joypad::button_info_container &&,
      sge::input::joypad::relative_axis_info_container &&,
      sge::input::joypad::ff::type_field,
      sge::input::info::name &&,
      sge::input::info::unique_id &&);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::absolute_axis_info_container const &
  absolute_axes() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::button_info_container const &
  buttons() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::relative_axis_info_container const &
  relative_axes() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::joypad::ff::type_field ff_types() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::info::name const &name() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::info::unique_id const &unique_id() const;

private:
  sge::input::joypad::absolute_axis_info_container absolute_axes_;

  sge::input::joypad::button_info_container buttons_;

  sge::input::joypad::relative_axis_info_container relative_axes_;

  sge::input::joypad::ff::type_field ff_types_;

  sge::input::info::name name_;

  sge::input::info::unique_id unique_id_;
};

}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_MOUSE_INFO_HPP_INCLUDED
#define SGE_INPUT_MOUSE_INFO_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/info_fwd.hpp> // IWYU pragma: keep

namespace sge::input::mouse
{

class info
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  info(
      sge::input::mouse::axis_info_container &&,
      sge::input::mouse::button_info_container &&,
      sge::input::info::name &&);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::axis_info_container const &axes() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::button_info_container const &
  buttons() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::info::name const &name() const;

private:
  sge::input::mouse::axis_info_container axes_;

  sge::input::mouse::button_info_container buttons_;

  sge::input::info::name name_;
};

}

#endif

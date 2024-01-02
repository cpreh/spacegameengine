//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_MOUSE_BUTTON_HPP_INCLUDED
#define SGE_INPUT_MOUSE_BUTTON_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_fwd.hpp> // IWYU pragma: keep
#include <sge/input/mouse/button_id.hpp>

namespace sge::input::mouse
{

class button
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  button(sge::input::mouse::button_code, sge::input::mouse::button_id);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::button_code code() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::button_id id() const;

private:
  sge::input::mouse::button_code code_;

  sge::input::mouse::button_id id_;
};

}

#endif

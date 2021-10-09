//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_MOUSE_AXIS_HPP_INCLUDED
#define SGE_INPUT_MOUSE_AXIS_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_fwd.hpp>
#include <sge/input/mouse/axis_id.hpp>

namespace sge::input::mouse
{

class axis
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  axis(sge::input::mouse::axis_code, sge::input::mouse::axis_id);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::axis_code code() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::axis_id id() const;

private:
  sge::input::mouse::axis_code code_;

  sge::input::mouse::axis_id id_;
};

}

#endif

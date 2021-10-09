//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_EVENT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_EVENT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/relative_movement/difference.hpp>
#include <sge/input/cursor/relative_movement/event_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::input::cursor::relative_movement
{

class SGE_CORE_DETAIL_CLASS_SYMBOL event : public sge::input::cursor::event::base
{
  FCPPT_NONMOVABLE(event);

public:
  SGE_INPUT_DETAIL_SYMBOL
  event(sge::input::cursor::shared_ptr, sge::input::cursor::relative_movement::difference);

  SGE_INPUT_DETAIL_SYMBOL
  ~event() override;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::cursor::relative_movement::difference
  difference() const;

private:
  sge::input::cursor::relative_movement::difference const difference_;
};

}

#endif

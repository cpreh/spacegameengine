//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_KEYBOARD_EVENT_DISCOVER_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_EVENT_DISCOVER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/base.hpp>
#include <sge/input/keyboard/event/discover_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::input::keyboard::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL discover : public sge::input::keyboard::event::base
{
  FCPPT_NONMOVABLE(discover);

public:
  SGE_INPUT_DETAIL_SYMBOL
  explicit discover(sge::input::keyboard::shared_ptr);

  SGE_INPUT_DETAIL_SYMBOL
  ~discover() override;
};

}

#endif

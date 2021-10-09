//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_FOCUS_EVENT_KEY_HPP_INCLUDED
#define SGE_INPUT_FOCUS_EVENT_KEY_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/key_fwd.hpp>
#include <sge/input/key/pressed.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::input::focus::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL key : public sge::input::focus::event::base
{
  FCPPT_NONMOVABLE(key);

public:
  SGE_INPUT_DETAIL_SYMBOL
  key(sge::input::focus::shared_ptr, sge::input::focus::key const &, sge::input::key::pressed);

  SGE_INPUT_DETAIL_SYMBOL
  ~key() override;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::focus::key const &get() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL bool pressed() const;

private:
  sge::input::focus::key const key_;

  sge::input::key::pressed const pressed_;
};

}

#endif

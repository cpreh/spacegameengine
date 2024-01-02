//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_FOCUS_MOD_STATE_TRACKER_HPP_INCLUDED
#define SGE_INPUT_FOCUS_MOD_STATE_TRACKER_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/mod_state_tracker_fwd.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base_fwd.hpp>
#include <sge/input/key/mod_state_fwd.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/input/key/pressed.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/shared_ptr_std_hash.hpp> // IWYU pragma: keep
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sge::input::focus
{

class mod_state_tracker
{
  FCPPT_NONMOVABLE(mod_state_tracker);

public:
  SGE_INPUT_DETAIL_SYMBOL
  mod_state_tracker();

  SGE_INPUT_DETAIL_SYMBOL
  ~mod_state_tracker();

  SGE_INPUT_DETAIL_SYMBOL
  void event(sge::input::focus::event::base const &);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::key::mod_state
  mod_state(sge::input::focus::shared_ptr const &) const;

private:
  using pressed_array = fcppt::enum_::array<sge::input::key::modifier, sge::input::key::pressed>;

  using map_type = std::unordered_map<sge::input::focus::shared_ptr, pressed_array>;

  map_type map_;
};

}

#endif

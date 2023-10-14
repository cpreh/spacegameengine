//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/wlinput/focus/keymap.hpp> // NOLINT(misc-include-cleaner)
#include <sge/wlinput/focus/keymap_ref.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::wlinput::focus::state::state(sge::wlinput::focus::keymap_ref const _keymap)
    : state_{::xkb_state_new(_keymap.get().get())}
{
  if (state_ == nullptr)
  {
    throw sge::input::exception{FCPPT_TEXT("Failed to create xkb state")};
  }
}

sge::wlinput::focus::state::state(state &&_other) noexcept : state_{_other.state_}
{
  _other.state_ = nullptr;
}

sge::wlinput::focus::state &sge::wlinput::focus::state::operator=(state &&_other) noexcept
{
  std::swap(state_, _other.state_);

  return *this;
}

sge::wlinput::focus::state::~state()
{
  // Ok to call this on nullptr
  ::xkb_state_unref(state_);
}

xkb_state *sge::wlinput::focus::state::get() const { return state_; }

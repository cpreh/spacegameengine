//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/wlinput/xkb_context.hpp>
#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/keymap.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::wlinput::focus::keymap::keymap(
    sge::wlinput::xkb_context_ref const _context, char const *const _string)
    : keymap_{::xkb_keymap_new_from_string(
          _context.get().get(), _string, XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS)}
{
  if (keymap_ == nullptr)
  {
    throw sge::input::exception{FCPPT_TEXT("Cannot create keymap")};
  }
}

sge::wlinput::focus::keymap::keymap(keymap &&_other) noexcept : keymap_{_other.keymap_}
{
  _other.keymap_ = nullptr;
}

sge::wlinput::focus::keymap &sge::wlinput::focus::keymap::operator=(keymap &&_other) noexcept
{
  std::swap(keymap_, _other.keymap_);

  return *this;
}

sge::wlinput::focus::keymap::~keymap() { ::xkb_keymap_unref(keymap_); }

xkb_keymap *sge::wlinput::focus::keymap::get() const { return keymap_; }

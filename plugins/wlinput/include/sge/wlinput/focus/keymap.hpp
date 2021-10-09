//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_FOCUS_KEYMAP_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_KEYMAP_HPP_INCLUDED

#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/keymap_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput::focus
{

class keymap
{
  FCPPT_NONCOPYABLE(keymap);

public:
  keymap(sge::wlinput::xkb_context_ref, char const *);

  keymap(keymap &&) noexcept;

  keymap &operator=(keymap &&) noexcept;

  ~keymap();

  [[nodiscard]] xkb_keymap *get() const;

private:
  xkb_keymap *keymap_;
};

}

#endif

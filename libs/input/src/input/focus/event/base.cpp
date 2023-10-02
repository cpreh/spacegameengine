//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/event_base.hpp>
#include <sge/input/focus/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::focus::event::base::base(sge::input::focus::shared_ptr _focus)
    : sge::input::event_base{_focus->window()}, focus_{std::move(_focus)}
{
}

sge::input::focus::event::base::~base() = default;

sge::input::focus::shared_ptr const &sge::input::focus::event::base::focus() const
{
  return focus_;
}

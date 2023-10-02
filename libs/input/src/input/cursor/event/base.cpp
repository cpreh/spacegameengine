//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/event_base.hpp>
#include <sge/input/cursor/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::event::base::base(sge::input::cursor::shared_ptr _cursor)
    : sge::input::event_base{_cursor->window()}, cursor_{std::move(_cursor)}
{
}

sge::input::cursor::event::base::~base() = default;

sge::input::cursor::shared_ptr const &sge::input::cursor::event::base::cursor() const
{
  return cursor_;
}

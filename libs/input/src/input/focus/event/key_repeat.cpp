//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/focus/key.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::focus::event::key_repeat::key_repeat(
    sge::input::focus::shared_ptr _focus, sge::input::focus::key const &_key)
    : sge::input::focus::event::base{std::move(_focus)}, key_{_key}
{
}

sge::input::focus::event::key_repeat::~key_repeat() = default;

sge::input::focus::key const &sge::input::focus::event::key_repeat::key() const { return key_; }

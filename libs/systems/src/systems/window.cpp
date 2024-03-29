//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::systems::window::window(sge::systems::window_source &&_source)
    : source_(std::move(_source)), show_(true), quit_(true)
{
}

sge::systems::window sge::systems::window::dont_show() &&
{
  show_ = false;

  return std::move(*this);
}

sge::systems::window sge::systems::window::dont_quit() &&
{
  quit_ = false;

  return std::move(*this);
}

sge::systems::window_source const &sge::systems::window::source() const { return source_; }

bool sge::systems::window::show() const { return show_; }

bool sge::systems::window::quit() const { return quit_; }

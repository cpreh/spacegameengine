//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/original_window.hpp>
#include <sge/window/default_class_name.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/window/title.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::systems::original_window::original_window(sge::window::title &&_title)
    : title_{std::move(_title)},
      class_name_{sge::window::default_class_name()},
      dim_{},
      hide_cursor_{false}
{
}

sge::systems::original_window sge::systems::original_window::dim(sge::window::dim const &_dim) &&
{
  dim_ = sge::window::optional_dim{_dim};

  return *this;
}

sge::systems::original_window
sge::systems::original_window::class_name(fcppt::string &&_class_name) &&
{
  class_name_ = fcppt::optional_string{std::move(_class_name)};

  return *this;
}

sge::systems::original_window sge::systems::original_window::hide_cursor() &&
{
  hide_cursor_ = true;

  return *this;
}

sge::window::title const &sge::systems::original_window::title() const { return title_; }

sge::window::optional_dim const &sge::systems::original_window::dim() const { return dim_; }

fcppt::optional_string const &sge::systems::original_window::class_name() const
{
  return class_name_;
}

bool sge::systems::original_window::get_hide_cursor() const { return hide_cursor_; }

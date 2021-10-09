//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/config.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_settings.hpp>
#include <sge/systems/optional_plugin_path.hpp>
#include <sge/systems/plugin_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::systems::config::config() : plugin_path_(), log_settings_() {}

sge::systems::config &sge::systems::config::plugin_path(std::filesystem::path &&_plugin_path)
{
  plugin_path_ =
      sge::systems::optional_plugin_path(sge::systems::plugin_path(std::move(_plugin_path)));

  return *this;
}

sge::systems::config &sge::systems::config::log_settings(sge::systems::log_settings &&_log_settings)
{
  log_settings_ = sge::systems::optional_log_settings(std::move(_log_settings));

  return *this;
}

sge::systems::optional_plugin_path const &sge::systems::config::plugin_path() const
{
  return plugin_path_;
}

sge::systems::optional_log_settings const &sge::systems::config::log_settings() const
{
  return log_settings_;
}

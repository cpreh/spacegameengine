//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/log/option_container.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_context_ref.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::systems::log_settings::log_settings(sge::log::option_container &&_options)
    : options_(std::move(_options)), log_context_()
{
}

sge::systems::log_settings
sge::systems::log_settings::log_context(fcppt::log::context_reference const _log_context) &&
{
  log_context_ = sge::systems::optional_log_context_ref{_log_context};

  return std::move(*this);
}

sge::log::option_container const &sge::systems::log_settings::options() const { return options_; }

sge::systems::optional_log_context_ref const &sge::systems::log_settings::log_context() const
{
  return log_context_;
}

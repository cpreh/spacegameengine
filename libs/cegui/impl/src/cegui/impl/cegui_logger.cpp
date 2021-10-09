//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/to_fcppt_string.hpp>
#include <sge/cegui/impl/cegui_logger.hpp>
#include <sge/log/default_parameters.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Logger.h>
#include <fcppt/config/external_end.hpp>

sge::cegui::impl::cegui_logger::cegui_logger(fcppt::log::object &_log)
    : CEGUI::Logger(),
      log_{_log, sge::log::default_parameters(fcppt::log::name{FCPPT_TEXT("CEGUI")})}
{
}

sge::cegui::impl::cegui_logger::~cegui_logger() = default;

void sge::cegui::impl::cegui_logger::logEvent(
    CEGUI::String const &_message, CEGUI::LoggingLevel const _level)
{
  fcppt::string const converted(fcppt::optional::from(
      sge::cegui::to_fcppt_string(_message),
      [] { return fcppt::string{FCPPT_TEXT("Failed to convert CEGUI string!")}; }));

  switch (_level)
  {
  case CEGUI::Errors:
    FCPPT_LOG_ERROR(log_, fcppt::log::out << converted)
    break;
  case CEGUI::Warnings:
    FCPPT_LOG_WARNING(log_, fcppt::log::out << converted)
    break;
  case CEGUI::Standard:
  case CEGUI::Informative:
    FCPPT_LOG_DEBUG(log_, fcppt::log::out << converted)
    break;
  case CEGUI::Insane:
    FCPPT_LOG_VERBOSE(log_, fcppt::log::out << converted)
    break;
  }
}

void sge::cegui::impl::cegui_logger::setLogFilename(CEGUI::String const &, bool)
{
  // ignored
}

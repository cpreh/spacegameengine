#include "../declare_local_logger.hpp"
#include <sge/cegui/detail/cegui_logger.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/io/color/set.hpp>
#include <fcppt/io/color/reset.hpp>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("cegui"))

void 
sge::cegui::detail::cegui_logger::logEvent(
	CEGUI::String const &message, 
	CEGUI::LoggingLevel const level)
{
	fcppt::string const converted = 
		fcppt::from_std_string(
			message.c_str());
	switch (level)
	{
		case CEGUI::Errors:
			FCPPT_LOG_FATAL(
				local_log,
				fcppt::log::_ << fcppt::io::color::set(fcppt::io::color::foreground::red,fcppt::io::color::background::black,fcppt::io::color::attribute::bold) << converted << fcppt::io::color::reset());
			break;
		case CEGUI::Warnings:
			FCPPT_LOG_WARNING(
				local_log,
				fcppt::log::_ << converted);
			break;
		case CEGUI::Standard:
			FCPPT_LOG_DEBUG(
				local_log,
				fcppt::log::_ << converted);
			break;
		case CEGUI::Informative:
			FCPPT_LOG_INFO(
				local_log,
				fcppt::log::_ << converted);
			break;
		case CEGUI::Insane:
			FCPPT_LOG_VERBOSE(
				local_log,
				fcppt::log::_ << converted);
			break;
	}
}

void 
sge::cegui::detail::cegui_logger::setLogFilename(
	CEGUI::String const &,
	bool)
{
	// ignored
}

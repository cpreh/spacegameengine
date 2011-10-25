/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/cegui/detail/cegui_logger.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/color/reset.hpp>
#include <fcppt/io/color/set.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("cegui"))

sge::cegui::detail::cegui_logger::cegui_logger()
{
}

sge::cegui::detail::cegui_logger::~cegui_logger()
{
}

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

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_CEGUI_LOGGER_HPP_INCLUDED
#define SGE_CEGUI_IMPL_CEGUI_LOGGER_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Logger.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class String;
}

namespace sge::cegui::impl
{

class cegui_logger
:
	public CEGUI::Logger
{
	FCPPT_NONMOVABLE(
		cegui_logger
	);
public:
	explicit
	cegui_logger(
		fcppt::log::object & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	~cegui_logger()
	override;
private:
	void
	logEvent(
		CEGUI::String const & message,
		CEGUI::LoggingLevel level
	)
	override;

	void
	setLogFilename(
		CEGUI::String const &filename,
		bool append
	)
	override;

	fcppt::log::object log_;
};

}

#endif

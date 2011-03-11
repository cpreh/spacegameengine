#ifndef SGE_CEGUI_DETAIL_LOGGER_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_LOGGER_HPP_INCLUDED

#include <CEGUI/CEGUILogger.h>

namespace sge
{
namespace cegui
{
namespace detail
{
class cegui_logger
:
	public CEGUI::Logger
{
public:
	void 
	logEvent(
		CEGUI::String const & message, 
		CEGUI::LoggingLevel level);

	void 
	setLogFilename(
		CEGUI::String const &filename,
		bool append);
};
}
}
}

#endif

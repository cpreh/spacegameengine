#ifndef SGE_CEGUI_CEGUI_LOGGER_HPP_INCLUDED
#define SGE_CEGUI_CEGUI_LOGGER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/cegui/symbol.hpp>
#include <CEGUI/CEGUILogger.h>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL cegui_logger
:
	public CEGUI::Logger
{
public:
	SGE_CEGUI_SYMBOL void 
	logEvent(
		CEGUI::String const & message, 
		CEGUI::LoggingLevel level);

	SGE_CEGUI_SYMBOL void 
	setLogFilename(
		CEGUI::String const &filename,
		bool append);
};
}
}

#endif

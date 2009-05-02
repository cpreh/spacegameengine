#include <sge/gui/exception.hpp>
#include <sge/text.hpp>

sge::gui::exception::exception(
	string const &what)
:
	sge::exception(SGE_TEXT("gui: ")+what)
{
}

#include <sge/cegui/exception.hpp>

sge::cegui::exception::exception(
	fcppt::string const &_string
)
:
	fcppt::exception(
		_string)
{}

sge::cegui::exception::~exception() throw()
{
}

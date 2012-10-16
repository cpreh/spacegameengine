#include <sge/shader/exception.hpp>
#include <fcppt/text.hpp>

sge::shader::exception::exception(
	fcppt::string const &_what)
:
	sge::exception(
		FCPPT_TEXT("shader: ")+_what)
{
}

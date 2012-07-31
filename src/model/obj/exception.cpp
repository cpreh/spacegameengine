#include <sge/exception.hpp>
#include <sge/model/obj/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sge::model::obj::exception::exception(
	fcppt::string const &_what)
:
	sge::exception(
		FCPPT_TEXT("obj: ")
		+_what)
{
}

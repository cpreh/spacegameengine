#include "../exception.hpp"
#include <sge/text.hpp>

sge::libpng::exception::exception(
	sge::string const &_message)
:
	sge::exception(SGE_TEXT("png: ")+_message)
{
}

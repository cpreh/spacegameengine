#include "../general_error.hpp"
#include <sge/text.hpp>

sge::libpng::general_error::general_error(
	sge::string const &_string)
:
	sge::exception(
		SGE_TEXT("png error: ")+_string)
{
}

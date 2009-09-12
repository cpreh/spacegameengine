#include "../unsupported_format.hpp"
#include <sge/text.hpp>

sge::libpng::unsupported_format::unsupported_format(
	sge::string const &_string)
:
	sge::exception(
		SGE_TEXT("png file has unsupported format: ")+_string)
{
}

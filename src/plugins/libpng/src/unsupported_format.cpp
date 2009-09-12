#include "../unsupported_format.hpp"
#include <sge/text.hpp>

sge::libpng::unsupported_format::unsupported_format(
	filesystem::path const &_path,
	sge::string const &_string)
:
	file_exception(
		_path,
		SGE_TEXT("file has unsupported format: ")+_string)
{
}

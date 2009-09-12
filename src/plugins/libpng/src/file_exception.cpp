#include "../file_exception.hpp"
#include <sge/text.hpp>

sge::libpng::file_exception::file_exception(
	filesystem::path const &_path,
	sge::string const &_message)
:
	exception(SGE_TEXT("\"")+_path.string()+SGE_TEXT("\": ")+_message)
{
}

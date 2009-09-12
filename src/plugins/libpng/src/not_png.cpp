#include "../not_png.hpp"
#include <sge/text.hpp>

sge::libpng::not_png::not_png(
	filesystem::path const &_path)
:
	file_exception(
		_path,
		SGE_TEXT("not a png file"))
{
}

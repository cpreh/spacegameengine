#include "../not_png.hpp"
#include <sge/text.hpp>

sge::libpng::not_png::not_png(
	filesystem::path const &_path)
:
	sge::exception(
		SGE_TEXT("\"")+_path.string()+SGE_TEXT("\"is not a png file"))
{
}

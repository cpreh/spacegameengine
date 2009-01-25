#include <sge/gui/media_path.hpp>
#include <sge/media_path.hpp>

sge::filesystem::path const sge::gui::media_path()
{
	return sge::media_path()/SGE_TEXT("gui");
}

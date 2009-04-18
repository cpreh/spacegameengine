#include <sge/gui/media_path.hpp>
#include <sge/config/media_path.hpp>

sge::filesystem::path const sge::gui::media_path()
{
	return sge::config::media_path();
}

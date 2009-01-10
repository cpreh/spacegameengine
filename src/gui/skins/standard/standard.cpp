#include <sge/gui/skins/standard.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/media.hpp>
#include <sge/text.hpp>

sge::gui::skins::standard::standard()
:
	bgcolor(renderer::colors::grey()),
	bgcolor_focused(renderer::colors::lightgrey())
{
}

sge::filesystem::path const
sge::gui::skins::standard::cursor_path() const
{
	return media_path()/SGE_TEXT("mainskin")/SGE_TEXT("cursor_pressed.png");
}

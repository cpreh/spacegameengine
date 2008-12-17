#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/media.hpp>

sge::gui::skins::standard::standard()
	: bgcolor(renderer::colors::grey()),
		bgcolor_focused(renderer::colors::lightgrey())
{
}

sge::path const sge::gui::skins::standard::cursor_path() const
{
	return media_path()/SGE_TEXT("mainskin")/SGE_TEXT("cursor_pressed.png");
}

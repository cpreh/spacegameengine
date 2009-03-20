#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/media_path.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/media.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins: standard"),
	false);
}

sge::gui::skins::standard::standard()
:
	bgcolor(renderer::colors::grey()),
	bgcolor_focused(renderer::colors::lightgrey())
{
}

sge::filesystem::path const
sge::gui::skins::standard::cursor_path() const
{
	return media_path() / SGE_TEXT("gui") / SGE_TEXT("cursor.png");
}

SGE_GUI_SKIN_DRAW_RETURN(widget) sge::gui::skins::standard::fallback(
	SGE_GUI_SKIN_DRAW_PARAMS_NAMED(widget))
{
	resize_buffer(w);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("buffer size is ")
		        << w.buffer().width() << SGE_TEXT(",") << w.buffer().height());

	canvas::object c(w.buffer());

	c.draw_rect(
		rect(c.size()),
		internal_color(0x0,0x0,0x0,0x0),
		canvas::rect_type::solid);
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting to texture"));

	blit_invalid(
		w,
		c,
		e,
		false);
}

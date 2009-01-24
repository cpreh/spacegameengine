#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/make_const_image_view.hpp>
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

void sge::gui::skins::standard::fallback(
	widget const &w,
	events::invalid_area const &e)
{
	// resize internal buffer if neccessary
	if (w.buffer().width() != static_cast<image::coord_t>(w.size().w()) ||
	    w.buffer().height() != static_cast<image::coord_t>(w.size().h()))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("resizing from ") 
			        << dim(w.buffer().width(),w.buffer().height())
							<< SGE_TEXT(" to ")
							<< w.size());
		w.buffer() = image(
			static_cast<image::coord_t>(w.size().w()),
			static_cast<image::coord_t>(w.size().h()));
	}

	canvas::object c(w.buffer());

	// Background
	c.draw_rect(
		rect(c.size()),
		internal_color(0xee,0xeb,0xe7,0xff),
		canvas::rect_type::solid);
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting to texture"));

	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(w.pos(),c.size()),
		e.texture(),
		e.area());
}

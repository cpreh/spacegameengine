#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/log.hpp>
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

void sge::gui::skins::standard::fallback(
	widget const &w,
	events::invalid_area const &e)
{
	resize_buffer(w);

	canvas::object c(w.buffer());

	// Background
	/*
	c.draw_rect(
		rect(c.size()),
		internal_color(0xee,0xeb,0xe7,0xff),
		canvas::rect_type::solid);
		*/
	c.draw_rect(
		rect(c.size()),
		internal_color(0x0,0x0,0x0,0x0),
		canvas::rect_type::solid);
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting to texture"));

	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(
			w.absolute_pos(),
			c.size()),
		e.texture(),
		e.area());
}

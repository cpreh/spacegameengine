#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/media_path.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/font/system.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins: standard"),
	false);
}

sge::gui::skins::standard::standard(
	font::system_ptr const fs)
:
	standard_font_(
		fs->create_font(
			media_path()/
			SGE_TEXT("fonts")/
			SGE_TEXT("default.ttf"),
			static_cast<font::size_type>(
				15)),
		renderer::colors::black())
{
}

SGE_GUI_SKIN_DRAW_RETURN(widgets::base) sge::gui::skins::standard::fallback(
	SGE_GUI_SKIN_DRAW_PARAMS(widgets::base))
{
	/*
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
		true);
	*/
}

sge::gui::font_info const sge::gui::skins::standard::standard_font() const
{
	return standard_font_;
}

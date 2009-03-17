#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins::standard::backdrop"),
	false);
}

void sge::gui::skins::standard::draw(
	widgets::backdrop const &w,
	events::invalid_area const &e)
{
	resize_buffer(w);

	canvas::object c(w.buffer());

	// Background
	c.draw_rect(
		rect(c.size()),
		internal_color(0xee,0xeb,0xe7,0xff),
		canvas::rect_type::solid);

	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(
			w.absolute_pos(),
			c.size()),
		e.texture(),
		e.area());
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::backdrop const &) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("size_hint called for backdrop, returning null"));
	return dim::null();
}

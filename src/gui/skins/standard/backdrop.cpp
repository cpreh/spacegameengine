#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins::standard::backdrop"),
	true);
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

	blit_invalid(w,c,e);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::backdrop const &) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("optimal_size called for backdrop, returning null"));
	return dim::null();
}

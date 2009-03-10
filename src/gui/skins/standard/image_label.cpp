#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/image_label.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins::standard::image_label"),
	false);
}

void sge::gui::skins::standard::draw(
	widgets::image_label const &w,
	events::invalid_area const &e)
{
	canvas::object c(w.buffer());
	blit_invalid(
		w,
		c,
		e);
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::image_label const &b) const
{
	return b.size();
}

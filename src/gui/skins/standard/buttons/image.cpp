#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/unit.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/gui/widgets/buttons/image.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins: standard: buttons: image"),
	false);

sge::gui::image const &choose_image(
	sge::gui::widgets::buttons::image const &b)
{
	if (b.mouse_over())
	{
		if (b.key_over())
			return *b.hover_keyboard();
		return *b.hover();
	}

	if (b.key_over())
		return *b.keyboard();

	return b.buffer() = *b.normal();
}
}

void sge::gui::skins::standard::draw(
	widgets::buttons::image const &b,
	events::invalid_area const &e)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("creating canvas from buffer"));
	
	b.buffer() = choose_image(b);

	canvas::object c(b.buffer());

	blit_invalid(b,c,e);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::buttons::image const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("returning button dimension ")
		        << b.normal()->size());

	return b.normal()->size();
}

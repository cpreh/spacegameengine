#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/renderer/colors.hpp>

sge::gui::skins::standard::standard()
	: bgcolor(renderer::colors::grey()),
		bgcolor_focused(renderer::colors::lightgrey())
{
}

void sge::gui::skins::standard::operator()(
	widgets::button &b,
	events::invalid_area const &e)
{
	canvas c = e.canvas();
	
	c.draw_rect(
		b.relative_area(),
		b.mouse_over() ? bgcolor_focused : bgcolor,
		rect_type::filled);

	SGE_ASSERT_MESSAGE(b.font(),SGE_TEXT("button: font missing while drawing button"));

	// reset font
	c.reset_font(
		b.font(),
		renderer::colors::black());
	
	// draw text centered
	c.draw_text(
		b.text(),
		point::null(),
		b.size(),
		font::align_h::center,
		font::align_v::center);
}

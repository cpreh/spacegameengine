#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/invalid_area.hpp>

sge::gui::skins::standard::standard()
	: bgcolor(renderer::colors::grey),
		bgcolor_focused(renderer::colors::lightgrey)
{
}

void sge::gui::skins::standard::operator()(
	widgets::button &b,
	events::invalid_area const &e)
{
	canvas c = e.canvas();
	
	color const col = b.mouse_over() ? bgcolor_focused : bgcolor;

	c.draw_rect(
		b.relative_area(),
		col,
		rect_type::filled);

	SGE_ASSERT_MESSAGE(b.font(),SGE_TEXT("button: font missing while drawing button"));

	// reset font
	c.reset_font(
		b.font(),
		renderer::colors::black,
		col);
	
	// draw text centered
	c.draw_text(
		b.text(),
		b.point(),
		b.size(),
		font::align_h::center,
		font::align_v::center);
}

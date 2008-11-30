#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/media.hpp>

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

	// Background
	c.draw_rect(
		b.relative_area(),
		b.mouse_over() 
			? internal_color(0xee,0xeb,0xe7,0xff)
			: internal_color(0xdc,0xda,0xd5,0xff),
		rect_type::filled);
	
	c.draw_line(
		point(0,0),
		point(b.relative_area().w()-1,0),
		internal_color(0xff,0xff,0xff,0xff));

	c.draw_line(
		point(0,0),
		point(0,b.relative_area().h()-1),
		internal_color(0xff,0xff,0xff,0xff));

	c.draw_line(
		point(b.relative_area().w()-2,1),
		point(b.relative_area().w()-2,b.relative_area().h()-2),
		internal_color(0x9e,0x9a,0x91,0xff));

	c.draw_line(
		point(1,b.relative_area().h()-2),
		point(b.relative_area().w()-2,b.relative_area().h()-2),
		internal_color(0x9e,0x9a,0x91,0xff));

	c.draw_line(
		point(b.relative_area().w()-1,0),
		point(b.relative_area().w()-1,b.relative_area().h()-1),
		internal_color(0x00,0x00,0x00,0x00));

	c.draw_line(
		point(0,b.relative_area().h()-1),
		point(b.relative_area().w()-1,b.relative_area().h()-1),
		internal_color(0x00,0x00,0x00,0x00));
	
	if (b.key_over())
	{
		c.draw_line(
			point(2,2),
			point(b.relative_area().w()-3,2),
			internal_color(0x00,0x00,0x00,0x00),
			true);

		c.draw_line(
			point(b.relative_area().w()-3,2),
			point(b.relative_area().w()-3,b.relative_area().h()-3),
			internal_color(0x00,0x00,0x00,0x00),
			true);

		c.draw_line(
			point(b.relative_area().w()-3,b.relative_area().h()-3),
			point(2,b.relative_area().h()-3),
			internal_color(0x00,0x00,0x00,0x00),
			true);

		c.draw_line(
			point(2,b.relative_area().h()-3),
			point(2,2),
			internal_color(0x00,0x00,0x00,0x00),
			true);
	}

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

sge::path const sge::gui::skins::standard::cursor_path() const
{
	return media_path()/SGE_TEXT("mainskin")/SGE_TEXT("cursor_pressed.png");
}

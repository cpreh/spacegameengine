#include "button.hpp"
#include "../manager.hpp"
#include "../events/invalid_area.hpp"
#include "../max_dim.hpp"
#include "../font_drawer_canvas.hpp"
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/iostream.hpp>
#include <sge/font/font.hpp>
#include <sge/math/rect_impl.hpp>

sge::gui::widgets::button::button(
	parent_data parent_,
	string const &text_,
	font::metrics_ptr _font,
	point const &p,
	dim const &d)
	: widget(parent_,size_policy::dynamic,p,d),
	  text_(text_),
	  font_(_font),
		mouse_over(false)
{
	if (!font_)
		font_ = parent_manager().standard_font();

	assert(font_);
}

void sge::gui::widgets::button::process(events::invalid_area const &e)
{
	//cerr << "button: drawing myself\n";

	canvas c = e.canvas();

	// fill with grey
	//cerr << "button: drawing rect " << relative_area() << "\n";
	
	renderer::color const col = 
		mouse_over ? 
			parent_manager().standard_color_focused() : 
			parent_manager().standard_color();

	c.draw_rect(
		relative_area(),
		col,
		rect_type::filled);

	assert(font_);

	// reset font
	c.reset_font(
		font_,
		sge::renderer::colors::black,
		col);

	//cerr << "button: drawing font in rect " << widget::size() << "\n";
	
	// draw text centered
	c.draw_text(
		text_,
		point(static_cast<unit>(0),static_cast<unit>(0)),
		widget::size(),
		font::align_h::center,
		font::align_v::center);
}

sge::gui::dim sge::gui::widgets::button::minimum_size() const
{
	font::font fn(font_,font::drawer_ptr());	
	// NOTE: we have to give text_size a huge rectangle because it won't
	// return a valid rectangle otherwise
	
	dim const font_dim = math::structure_cast<unit>(
		fn.text_size(text_,math::max_dim<font::unit>()).size());

	return dim(static_cast<unit>(font_dim.w()+2),static_cast<unit>(font_dim.h()+2));
}

void sge::gui::widgets::button::do_size(dim const &s)
{
	set_size_raw(s);
}

void sge::gui::widgets::button::do_pos(point const &s)
{
	set_pos_raw(s);
}

void sge::gui::widgets::button::do_compile()
{
}

void sge::gui::widgets::button::process(events::mouse_enter const &)
{
	mouse_over = true;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_leave const &)
{
	mouse_over = false;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_click const &m)
{
	clicked();
}

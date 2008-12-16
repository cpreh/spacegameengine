#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/timer/object.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/time/second.hpp>
#include <sge/gui/manager.hpp>
#include <boost/bind.hpp>

sge::gui::widgets::edit::edit(
	parent_data parent,
	dim const &desired_size_,
	font::metrics_ptr const font_)
	: widget(parent),
	  font_(font_),
		desired_size_(desired_size_),
		cursor_visible_(cursor_visible_),
		buffer_()
{
}

sge::gui::dim const sge::gui::widgets::edit::size_hint() const
{
	
	return sge::gui::dim();
}

sge::string const sge::gui::widgets::edit::text() const
{
	return text_;
}

sge::font::metrics_ptr const sge::gui::widgets::edit::font() const
{
	return font_;
}

void sge::gui::widgets::edit::process(events::invalid_area const &)
{
	/*
	canvas &c = e.canvas();
	
	// fill background
	c.draw_rect(
		relative_area(),
		internal_color(0xff,0xff,0xff,0xff),
		rect_type::solid);
	
	font::font f(font_);
	dim const ts = math::structure_cast<unit>(
		f.text_size(
			text_,
			math::max_dim<font::unit>()).size());
	
	resize(
		math::vector<bool,2>(
			ts.w() > static_cast<unit>(buffer_.width()),
			ts.h() > static_cast<unit>(buffer_.height())));

	font.draw_text(
		text_,
		font::pos::null(),
		math::max_dim<font::unit>());
		*/
}

void sge::gui::widgets::edit::process(events::keyboard_enter const &)
{
	timer_ = 
		parent_manager().register_timer(
			sge::time::second(1),
			boost::bind(&edit::blink_callback,this));
}

sge::gui::key_handling::type sge::gui::widgets::edit::process(events::key const &)
{
	return key_handling::process;
}

void sge::gui::widgets::edit::process(events::keyboard_leave const &)
{
	timer_.reset();
}

void sge::gui::widgets::edit::blink_callback()
{
	cursor_visible_ = !cursor_visible_;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::edit::resize(math::vector<bool,2> const &b)
{
	if (!b.x() && !b.y())
		return;
	
	point n = point(
		static_cast<unit>(buffer_.width()),
		static_cast<unit>(buffer_.height()));
	
	if (b.x())
		n.x() *= 2;
	
	if (b.y())
		n.y() *= 2;
	
	image nb(
		static_cast<image::coord_t>(n.x()),
		static_cast<image::coord_t>(n.y()));

	/*
	renderer::copy_and_convert_pixels(
		renderer::make_const_image_view(
			boost::gil::view(buffer_)),
		renderer::subimage_view(
			boost::gil::view(nb),
			renderer::lock_rect(
				static_cast<renderer::size_type>(buffer_.width()),
				static_cast<renderer::size_type>(buffer_.height()))));
	*/
	
	buffer_ = nb;
}

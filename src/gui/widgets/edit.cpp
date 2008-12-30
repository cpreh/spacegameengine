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
		buffer_(),
		scroll_pos_(point::null())
{
}

sge::string const sge::gui::widgets::edit::text() const
{
	return text_;
}

sge::font::metrics_ptr const sge::gui::widgets::edit::font() const
{
	return font_;
}

sge::gui::point const &sge::gui::widgets::edit::scroll_pos() const
{
	return scroll_pos_;
}

sge::gui::dim const sge::gui::widgets::edit::desired_size() const
{
	return desired_size_;
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
		n.x() *= static_cast<unit>(2);
	
	if (b.y())
		n.y() *= static_cast<unit>(2);
	
	image nb(
		static_cast<image::coord_t>(n.x()),
		static_cast<image::coord_t>(n.y()));
	
	buffer_ = nb;
}

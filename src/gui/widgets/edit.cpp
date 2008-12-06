#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/timer/object.hpp>
#include <sge/time/second.hpp>
#include <sge/gui/manager.hpp>
#include <boost/bind.hpp>

sge::gui::widgets::edit::edit(
	parent_data parent,
	dim const &desired_size_,
	font::metrics_ptr const font_)
	: widget(parent),
	  font_(font_),
		desired_size_(desired_size_)
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
	
}

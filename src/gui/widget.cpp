#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/manager.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/rect_impl.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("widget"),true);
}

sge::gui::widget::widget(
	parent_data parent_data_,
	size_policy_t const &size_policy_,
	keyboard_focus::type keyboard_focus_)
	:	parent_(parent_data_.parent_widget()),
	  manager_(parent_data_.parent_manager()),
		pos_(point::null()),
		size_(dim::null()),
		size_policy_(size_policy_),
		keyboard_focus_(keyboard_focus_)
{
	if (parent_widget())
		parent_widget()->add_child(*this);
	else
		parent_manager().add(*this);
}

sge::gui::point const &sge::gui::widget::pos() const
{
	return pos_;
}

sge::gui::dim const &sge::gui::widget::size() const
{
	return size_;
}

sge::gui::manager &sge::gui::widget::parent_manager() 
{ 
	return manager_; 
}

sge::gui::manager const &sge::gui::widget::parent_manager() const 
{ 
	return manager_; 
}

sge::gui::widgets::container *sge::gui::widget::parent_widget() 
{ 
	return parent_; 
}

sge::gui::widgets::container const *sge::gui::widget::parent_widget() const 
{ 
	return parent_; 
}

sge::gui::widget::size_policy_t const &sge::gui::widget::size_policy() const 
{
	return size_policy_; 
}

void sge::gui::widget::size_policy(size_policy_t const &s) 
{ 
	size_policy_ = s; 
}

sge::gui::keyboard_focus::type sge::gui::widget::keyboard_focus() const
{
	return keyboard_focus_;
}

void sge::gui::widget::keyboard_focus(keyboard_focus::type const n)
{
	parent_manager().keyboard().keyboard_focus(*this,keyboard_focus_ = n);
}

void sge::gui::widget::size(dim const &d)
{
	set_size_raw(d);
	compile();
}

void sge::gui::widget::pos(point const &d)
{
	set_pos_raw(d);

	// is this widget a top level widget? then call the manager to reposition the
	// underlying sprite
	if (!parent_widget())
		parent_manager().reposition(*this,d);
}

void sge::gui::widget::compile()
{
	SGE_LOG_DEBUG(mylogger,log::_1 << "compiling");

	if (parent_widget())
	{
		parent_widget()->compile();
		return;
	}
	
	SGE_LOG_DEBUG(mylogger,log::_1 << "running do_compile");
	set_size_raw(size_hint());
	do_compile();

	// signal manager to recompile according to (new) size and position
	SGE_LOG_DEBUG(mylogger,log::_1 << "running manager::compile");
	parent_manager().compile(*this);
}

void sge::gui::widget::process(events::invalid_area const &e)
{
	parent_manager().skin()->draw(*this,e);
}

void sge::gui::widget::process(events::mouse_enter const &) {}
void sge::gui::widget::process(events::mouse_leave const &) {}
void sge::gui::widget::process(events::mouse_move const &) {}
void sge::gui::widget::process(events::mouse_click const &) {}

void sge::gui::widget::process(events::key const &) 
{
}

void sge::gui::widget::process(events::keyboard_enter const &) 
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
}

void sge::gui::widget::process(events::keyboard_leave const &) 
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
}

bool sge::gui::widget::is_container() const
{
	return dynamic_cast<widgets::container const *>(this);
}

sge::gui::widget::~widget()
{
	if (parent_widget())
		parent_widget()->remove_child(*this);
	else
		parent_manager().remove(*this);
}

sge::gui::rect const sge::gui::widget::relative_area() const
{
	return rect(point(static_cast<unit>(0),static_cast<unit>(0)), size());
}

sge::gui::rect const sge::gui::widget::absolute_area() const
{
	return rect(pos(), size());
}

void sge::gui::widget::set_size_raw(dim const &d) 
{ 
	size_ = d; 
}

void sge::gui::widget::set_pos_raw(point const &p) 
{ 
	pos_ = p; 
}

void sge::gui::widget::do_compile() 
{
}

sge::gui::widget *sge::gui::widget::do_recalculate_focus(point const &) 
{ 
	return this; 
}

sge::gui::widget *sge::gui::widget::recalculate_focus(point const &mouse_click)
{
	// pointer is no longer inside widget area
	if (!math::contains(absolute_area(),mouse_click))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("mouse no longer inside widget, sending leave"));

		process(events::mouse_leave());
		
		if (!parent_widget())
			return 0;

		return parent_widget()->recalculate_focus(mouse_click);
	}

	widget *const new_focus = do_recalculate_focus(mouse_click);
	if (new_focus == this)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("focus hasn't changed, sending mouse_move"));
		process(events::mouse_move(mouse_click));
	}
	return new_focus;
}

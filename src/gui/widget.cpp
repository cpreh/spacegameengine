#include "utility/ptr_delete_first.hpp"
#include <sge/gui/widget.hpp>
#include <sge/gui/layout.hpp>
#include <sge/gui/layouts/null.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/manager.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("widget"),false);
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
		keyboard_focus_(keyboard_focus_),
		layout_(new layouts::null(*this))
{
	if (parent_widget())
		parent_widget()->add_child(*this);
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

sge::gui::image &sge::gui::widget::buffer() const
{
	return buffer_;
}

sge::gui::manager &sge::gui::widget::parent_manager() 
{ 
	return manager_; 
}

sge::gui::manager const &sge::gui::widget::parent_manager() const 
{ 
	return manager_; 
}

sge::gui::widget *sge::gui::widget::parent_widget() 
{ 
	return parent_; 
}

sge::gui::widget const *sge::gui::widget::parent_widget() const 
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

sge::gui::widget::child_container &sge::gui::widget::children()
{
	return children_;
}

sge::gui::widget::child_container const &sge::gui::widget::children() const
{
	return children_;
}

void sge::gui::widget::add_child(widget &w)
{
	children_.push_back(&w);
}

void sge::gui::widget::remove_child(widget &w)
{
	utility::ptr_delete_first(children_,&w);
}

void sge::gui::widget::layout(layout_auto_ptr n)
{
	SGE_ASSERT_MESSAGE(
		&(n->connected_widget()) == this,
		SGE_TEXT("widget specified for layout is not the widget the layout is assigned to"));
		
	layout_ = n;
}

sge::gui::layout_ptr sge::gui::widget::layout()
{ 
	return layout_.get(); 
}

sge::gui::const_layout_ptr sge::gui::widget::layout() const 
{ 
	return layout_.get(); 
}

bool sge::gui::widget::has_child(widget const &w) const
{
	BOOST_FOREACH(widget const &child,children())
	{
		if (&w == &child)
			return true;

		if (child.has_child(w))
			return true;
	}

	return false;
}

void sge::gui::widget::size(dim const &d)
{
	layout()->size(d);
}

void sge::gui::widget::pos(point const &d)
{
	layout()->pos(d);
}

void sge::gui::widget::compile()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in compile"));
	layout()->update();
}

sge::gui::dim const sge::gui::widget::size_hint() const
{
	return layout()->size_hint();
}

void sge::gui::widget::process(events::invalid_area const &e)
{
	// draw itself, then draw children
	parent_manager().skin()->draw(*this,e);

	BOOST_FOREACH(widget &w,children())
		if (math::intersects(e.area(),w.absolute_area()))
			w.process(e);
}

void sge::gui::widget::process(events::mouse_enter const &) {}
void sge::gui::widget::process(events::mouse_leave const &) {}
void sge::gui::widget::process(events::mouse_move const &) {}
void sge::gui::widget::process(events::mouse_click const &) {}

sge::gui::key_handling::type sge::gui::widget::process(events::key const &) 
{ 
	return key_handling::process; 
}

void sge::gui::widget::process(events::keyboard_enter const &) 
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
}

void sge::gui::widget::process(events::keyboard_leave const &) 
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
}

sge::gui::widget::~widget()
{
	if (parent_widget())
		parent_widget()->remove_child(*this);
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
	parent_manager().resize(*this,d);
}

void sge::gui::widget::set_pos_raw(point const &p) 
{ 
	pos_ = p; 
	parent_manager().reposition(*this,p);
}

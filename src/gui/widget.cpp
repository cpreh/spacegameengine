#include "utility/ptr_delete_first.hpp"
#include <sge/gui/widget.hpp>
#include <sge/gui/layout.hpp>
#include <sge/gui/layouts/null.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/manager.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/assert.hpp>
#include <sge/cerr.hpp>
#include <sge/math/rect_util.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("widget"),
	false);
}

sge::gui::widget::widget(
	parent_data const &parent_data_,
	parameters const &params)
	:	parent_(parent_data_.parent_widget()),
	  manager_(parent_data_.parent_manager()),
		pos_(params.pos()),
		size_(params.size()),
		size_policy_(params.size_policy()),
		keyboard_focus_(params.keyboard_focus()),
		layout_(
			params.layout() 
			? params.layout() 
			: layout_auto_ptr(new layouts::null(*this))),
		activation_(params.activation())
{
	SGE_ASSERT_MESSAGE(
		&(layout_->connected_widget()) == this,
		SGE_TEXT("widget specified for layout is not the widget the layout is assigned to"));

	if (has_parent())
		parent_widget().add_child(*this);
	parent_manager().add(*this);
}

sge::gui::point const sge::gui::widget::screen_pos() const
{
	if (!has_parent())
		return pos_;
	return pos_ + parent_widget().screen_pos();
}

sge::gui::point const sge::gui::widget::absolute_pos() const
{
	if (!has_parent())
		return point::null();
	if (!parent_widget().has_parent())
		return pos_;
	return pos_ + parent_widget().absolute_pos();
}

sge::gui::point const sge::gui::widget::relative_pos() const
{
	if (!has_parent())
		return point::null();
	return pos_;
}

sge::gui::dim const sge::gui::widget::size() const
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

sge::gui::widget &sge::gui::widget::parent_widget() 
{ 
	return *parent_; 
}

sge::gui::widget const &sge::gui::widget::parent_widget() const 
{ 
	return *parent_; 
}

bool sge::gui::widget::has_parent() const
{
	return parent_;
}

sge::gui::widget &sge::gui::widget::oldest_parent()
{ 
	if (!has_parent())
		return *this;
	return parent_widget().oldest_parent();
}

sge::gui::widget const &sge::gui::widget::oldest_parent() const 
{ 
	if (!has_parent())
		return *this;
	return parent_widget().oldest_parent();
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

void sge::gui::widget::activation(activation_state::type _activation)
{
	if (_activation == activation())
		return;
	activation_ = _activation;
	parent_manager().activation(*this,activation_);
}

sge::gui::activation_state::type sge::gui::widget::activation() const
{
	return activation_;
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

void sge::gui::widget::relative_pos(point const &d)
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
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("redrawing myself, region ")
		        << e.area());
	parent_manager().skin().draw(*this,e);

	BOOST_FOREACH(widget &w,children())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("checking if ")
			        << w.absolute_area()
							<< SGE_TEXT(" intersects with ")
							<< e.area() 
							<< SGE_TEXT(": ")
							<< math::intersects(w.absolute_area(),e.area()));

		if (math::intersects(w.absolute_area(),e.area()))
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("sending widget ")
				        << typeid(w).name()
								<< SGE_TEXT(" an invalid area event"));
			w.process(e);
		}
	}
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
	if (has_parent())
		parent_widget().remove_child(*this);
	parent_manager().remove(*this);
}

sge::gui::rect const sge::gui::widget::absolute_area() const
{
	return rect(absolute_pos(), size());
}

sge::gui::rect const sge::gui::widget::screen_area() const
{
	return rect(screen_pos(), size());
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

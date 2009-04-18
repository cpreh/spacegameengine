#include <sge/algorithm/ptr_container_erase.hpp>
#include <sge/gui/widgets/base.hpp>
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

sge::gui::widgets::base::base(
	parent_data const &parent_data_,
	parameters const &params)
:	
	parent_(	
		parent_data_.parent_widget()),
	manager_(
		parent_data_.parent_manager()),
	pos_(
		point::null()),
	pos_hint_(
		params.pos()),
	size_(
		dim::null()),
	size_hint_(
		params.size()),
	size_policy_(
		params.size_policy()),
	keyboard_focus_(
		params.keyboard_focus()),
	layout_(
		params.layout() 
		? params.layout() 
		: layouts::auto_ptr(new layouts::null())),
	activation_(params.activation())
{
	layout_->connected_widget(*this);
	if (has_parent())
		parent_widget().add_child(*this);
	parent_manager().add(*this);
}

sge::gui::point const sge::gui::widgets::base::screen_pos() const
{
	if (!has_parent())
		return pos_;
	return pos_ + parent_widget().screen_pos();
}

sge::gui::point const sge::gui::widgets::base::absolute_pos() const
{
	if (!has_parent())
		return point::null();
	if (!parent_widget().has_parent())
		return pos_;
	return pos_ + parent_widget().absolute_pos();
}

sge::gui::point const sge::gui::widgets::base::relative_pos() const
{
	if (!has_parent())
		return point::null();
	return pos_;
}

sge::gui::dim const sge::gui::widgets::base::size() const
{
	return size_;
}

sge::gui::image &sge::gui::widgets::base::buffer() const
{
	return buffer_;
}

sge::gui::manager &sge::gui::widgets::base::parent_manager() 
{ 
	return manager_; 
}

sge::gui::manager const &sge::gui::widgets::base::parent_manager() const 
{ 
	return manager_; 
}

sge::gui::widgets::base &sge::gui::widgets::base::parent_widget() 
{ 
	return *parent_; 
}

sge::gui::widgets::base const &sge::gui::widgets::base::parent_widget() const 
{ 
	return *parent_; 
}

bool sge::gui::widgets::base::has_parent() const
{
	return parent_;
}

sge::gui::widgets::base &sge::gui::widgets::base::oldest_parent()
{ 
	if (!has_parent())
		return *this;
	return parent_widget().oldest_parent();
}

sge::gui::widgets::base const &sge::gui::widgets::base::oldest_parent() const 
{ 
	if (!has_parent())
		return *this;
	return parent_widget().oldest_parent();
}

sge::gui::size_policy const &sge::gui::widgets::base::size_policy() const 
{
	return size_policy_; 
}

void sge::gui::widgets::base::size_policy(sge::gui::size_policy const &s) 
{ 
	size_policy_ = s; 
}

sge::gui::keyboard_focus::type sge::gui::widgets::base::keyboard_focus() const
{
	return keyboard_focus_;
}

void sge::gui::widgets::base::keyboard_focus(keyboard_focus::type const n)
{
	parent_manager().keyboard_focus(
		*this,
		keyboard_focus_ = n);
}

sge::gui::widgets::base::child_container &sge::gui::widgets::base::children()
{
	return children_;
}

sge::gui::widgets::base::child_container const &sge::gui::widgets::base::children() const
{
	return children_;
}

void sge::gui::widgets::base::add_child(widgets::base &w)
{
	children_.push_back(&w);
}

void sge::gui::widgets::base::remove_child(widgets::base &w)
{
	algorithm::ptr_container_erase(
		children_,
		&w);
}

void sge::gui::widgets::base::activation(
	activation_state::type _activation)
{
	if (_activation == activation())
		return;
	activation_ = _activation;
	parent_manager().activation(*this,activation_);
}

sge::gui::activation_state::type sge::gui::widgets::base::activation() const
{
	return activation_;
}

void sge::gui::widgets::base::layout(layouts::auto_ptr n)
{
	layout_ = n;
	layout_->connected_widget(*this);
	invalidate(
		*this,
		invalidation::all);
}

sge::gui::layouts::base &sge::gui::widgets::base::layout()
{ 
	return *layout_; 
}

sge::gui::layouts::base const &sge::gui::widgets::base::layout() const 
{ 
	return *layout_; 
}

bool sge::gui::widgets::base::has_child(widgets::base const &w) const
{
	BOOST_FOREACH(widgets::base const &child,children())
	{
		if (&w == &child)
			return true;

		if (child.has_child(w))
			return true;
	}

	return false;
}

void sge::gui::widgets::base::size(
	dim const &_size_hint)
{
	size_hint_ = _size_hint;
	invalidate(
		*this,
		invalidation::size);
}

void sge::gui::widgets::base::pos(
	point const &_pos_hint)
{
	pos_hint_ = _pos_hint;
	invalidate(
		*this,
		invalidation::position);
}

void sge::gui::widgets::base::compile(
	invalidation::type const &i)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in compile"));
	layout().compile(
		i);
}

void sge::gui::widgets::base::invalidate(
	widgets::base &w,
	invalidation::type const &i)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in invalidate"));
	layout().invalidate(
		w,
		i);
}

sge::gui::dim const sge::gui::widgets::base::size_hint() const
{
	if (size_hint_)
		return *size_hint_;
	return layout().size_hint();
}

boost::optional<sge::gui::point> const sge::gui::widgets::base::pos_hint() const
{
	return pos_hint_;
}

void sge::gui::widgets::base::process(
	events::invalid_area const &e)
{
	// draw itself, then draw children
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("redrawing myself, region ")
		        << e.area());
	parent_manager().skin().draw(*this,e);

	BOOST_FOREACH(widgets::base &w,children())
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
				log::_1 << SGE_TEXT("sending widgets::base ")
				        << type_info(typeid(w)).name()
								<< SGE_TEXT(" an invalid area event"));
			w.process(e);
		}
	}
}

void sge::gui::widgets::base::process(events::mouse_enter const &) {}
void sge::gui::widgets::base::process(events::mouse_leave const &) {}
void sge::gui::widgets::base::process(events::mouse_move const &) {}
void sge::gui::widgets::base::process(events::mouse_click const &) {}

sge::gui::key_handling::type sge::gui::widgets::base::process(
	events::key const &) 
{ 
	return key_handling::process; 
}

void sge::gui::widgets::base::process(
	events::keyboard_enter const &) 
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
}

void sge::gui::widgets::base::process(
	events::keyboard_leave const &) 
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
}

sge::gui::widgets::base::~base()
{
	if (has_parent())
		parent_widget().remove_child(
			*this);
	parent_manager().remove(
		*this);
}

sge::gui::rect const sge::gui::widgets::base::absolute_area() const
{
	return rect(absolute_pos(), size());
}

sge::gui::rect const sge::gui::widgets::base::screen_area() const
{
	return rect(screen_pos(), size());
}

void sge::gui::widgets::base::set_size_raw(
	dim const &_size) 
{ 
	size_ = _size; 
	parent_manager().resize(
		*this,
		size_);
}

void sge::gui::widgets::base::set_pos_raw(
	point const &p) 
{ 
	pos_ = p; 
	parent_manager().reposition(
		*this,
		p);
}

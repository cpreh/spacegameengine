#include <sge/gui/widgets/container.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/events/mouse_enter.hpp>
#include <sge/gui/log.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("container"));
}

sge::gui::widgets::container::container(
	parent_data parent)
	: widget(
			parent,
			size_policy_t(
				axis_policy::type(axis_policy::can_grow) | axis_policy::can_shrink,
				axis_policy::type(axis_policy::can_grow) | axis_policy::can_shrink))
{
}

void sge::gui::widgets::container::add_child(widget &w)
{
	children_.push_back(&w);
}

void sge::gui::widgets::container::remove_child(widget &w)
{
	children_.erase_if(&boost::lambda::_1 == boost::lambda::constant(&w));
}

sge::gui::dim const sge::gui::widgets::container::size_hint() const
{
	SGE_ASSERT_MESSAGE(
		layout(),
		SGE_TEXT("container doesn't have a layout, yet tried to call size_hint"));
	
	// FIXME: make size_hint axis based (independent axes)
	if (size_hint_ != dim())
	{
		SGE_LOG_DEBUG(mylogger,
			log::_1 << SGE_TEXT("size hint manually set to ") << size_hint_);
		return size_hint_;
	}
	SGE_LOG_DEBUG(mylogger,
		log::_1 << SGE_TEXT("size hint calculated automatically to ") 
						<< layout()->size_hint());
	return layout()->size_hint();
}

void sge::gui::widgets::container::process(events::invalid_area const &e)
{
	BOOST_FOREACH(widget &w,children())
		if (math::intersects(w.absolute_area(),e.canvas().invalid_area()))
			w.process(
				events::invalid_area(
					canvas(
						e.canvas().view(),
						w.absolute_area(),
						e.canvas().invalid_area())));
}

void sge::gui::widgets::container::do_compile()
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("in do_compile"));
	SGE_ASSERT_MESSAGE(
		layout(),
		SGE_TEXT("container doesn't have a layout yet, tried to call do_compile"));
	layout()->update();
}

bool sge::gui::widgets::container::has_child(widget const &w) const
{
	BOOST_FOREACH(widget const &child,children())
	{
		if (&w == &child)
			return true;

		if (!child.is_container())
			continue;

		if (dynamic_cast<widgets::container const &>(child).has_child(w))
			return true;
	}

	return false;
}

sge::gui::widget *sge::gui::widgets::container::do_recalculate_focus(point const &p)
{
	BOOST_FOREACH(widget &child,children())
	{
		if (math::contains(child.absolute_area(),p))
		{
			SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("a child has the focus, sending enter"));
			child.process(events::mouse_enter(p));
			return child.do_recalculate_focus(p);
		}
	}
	
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("no child has the focus, doing nothing"));
	return this;
}

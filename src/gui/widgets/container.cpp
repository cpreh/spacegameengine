#include <sge/gui/widgets/container.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/events/mouse_enter.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>

sge::gui::widgets::container::container(
	parent_data parent,
	point const &p,
	dim const &d)
	: widget(
			parent,
			size_policy(
				axis_policy::preferred,
				axis_policy::preferred),
			p,
			d)
{
}

void sge::gui::widgets::container::add_child(widget &w)
{
	sge::cerr << "container: adding child\n";
	children_.push_back(&w);
}

void sge::gui::widgets::container::remove_child(widget &w)
{
	sge::cerr << "container: removing child\n";
	children_.erase_if(&boost::lambda::_1 == boost::lambda::constant(&w));
}

sge::gui::dim const sge::gui::widgets::container::size_hint() const
{
	SGE_ASSERT_MESSAGE(
		layout(),
		SGE_TEXT("container doesn't have a layout, yet tried to call size_hint"));

	return layout()->size_hint();
}

// TODO: this just brute force resizes the widget, even if it's in the middle of
// a layout hierarchy. we could implement a
// parent_widget().layout()->size_hint(n); here
void sge::gui::widgets::container::do_size(dim const &n)
{
	SGE_ASSERT_MESSAGE(
		layout(),
		SGE_TEXT("container doesn't have a layout, yet tried to call do_size"));

	set_size_raw(n);
}

void sge::gui::widgets::container::do_pos(point const &p)
{
	set_pos_raw(p);
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
	sge::cerr << "container: in do_compile\n";
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
			cerr << "container: a child has the focus, sending enter\n";
			child.process(events::mouse_enter(p));
			return child.do_recalculate_focus(p);
		}
	}
	
	cerr << "container: no child has the focus, doing nothing\n";
	return this;
}

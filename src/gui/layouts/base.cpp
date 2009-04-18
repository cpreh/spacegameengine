#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/manager.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::gui::layouts::base::base()
:
	w(0)
{
}

void sge::gui::layouts::base::invalidate(
	widgets::base&,
	invalidation::type const &t)
{
	if (connected_widget().has_parent())
		connected_widget().parent_widget().invalidate(
			connected_widget(),
			t);
	else
		connected_widget().parent_manager().invalidate(
			connected_widget(),
			t);
}

sge::gui::widgets::base&
sge::gui::layouts::base::connected_widget()
{
	return *w;
}

sge::gui::widgets::base const &
sge::gui::layouts::base::connected_widget() const
{
	return *w;
}

sge::gui::layouts::base::~base()
{}

void sge::gui::layouts::base::set_widget_size(
	widgets::base &w,
	dim const &d)
{
	w.set_size_raw(d);
}

void sge::gui::layouts::base::set_widget_pos(
	widgets::base &w,
	point const &d)
{
	w.set_pos_raw(d);
}

void sge::gui::layouts::base::compile_widget(
	widgets::base &w,
	invalidation::type const &)
{
	w.compile_static();
}

void sge::gui::layouts::base::connected_widget(widgets::base &_w)
{
	if (w)
		throw exception(SGE_TEXT("registered connected widgets::base twice"));
	
	w = &_w;
}

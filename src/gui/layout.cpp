#include <sge/gui/layout.hpp>
#include <sge/gui/widget.hpp>

sge::gui::layout::layout(widget &w)
:
	w(w)
{
}

sge::gui::widget &
sge::gui::layout::connected_widget()
{
	return w;
}

sge::gui::widget const &
sge::gui::layout::connected_widget() const
{
	return w;
}

sge::gui::layout::~layout()
{}

void sge::gui::layout::set_widget_size(widget &w,dim const &d)
{
	w.set_size_raw(d);
}

void sge::gui::layout::set_widget_pos(widget &w,point const &d)
{
	w.set_pos_raw(d);
}

void sge::gui::layout::compile_widget(widget &w)
{
	w.compile();
}

#include <sge/gui/layout.hpp>
#include <sge/gui/widget.hpp>
#include <sge/iostream.hpp>

sge::gui::layout::layout(widget &w)
	: w(w)
{
}

void sge::gui::layout::set_widget_size(widget &w,dim const &d)
{
	w.set_size_raw(d);
}

void sge::gui::layout::set_widget_pos(widget &w,point const &d)
{
	w.set_pos_raw(d);
}

void sge::gui::layout::widget_compile(widget &w)
{
	w.do_compile();
}

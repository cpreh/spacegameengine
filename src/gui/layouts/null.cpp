#include <sge/gui/layouts/null.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>

sge::gui::layouts::null::null(widget &w)
	: layout(w)
{
}

void sge::gui::layouts::null::update()
{
}

void sge::gui::layouts::null::pos(point const &p)
{
	layout::set_widget_pos(connected_widget(),p);
}

void sge::gui::layouts::null::size(dim const &p)
{
	layout::set_widget_size(connected_widget(),p);
}

sge::gui::dim const sge::gui::layouts::null::size_hint() const
{
	return connected_widget().parent_manager().skin()->size_hint(
		connected_widget());
}

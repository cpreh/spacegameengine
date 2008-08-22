#include <sge/gui/widgets/container.hpp>

sge::gui::widget::parent_data::parent_data(widgets::container &wref)
	: widget_(&wref),manager_(wref.parent_manager())
{
}

sge::gui::widget::parent_data::parent_data(manager &manager_)
	: widget_(0),manager_(manager_)
{
}

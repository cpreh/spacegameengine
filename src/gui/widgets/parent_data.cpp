#include <sge/gui/widgets/base.hpp>
#include <sge/gui/widgets/parent_data.hpp>

sge::gui::widgets::parent_data::parent_data(
	base &wref)
: 
	widget_(&wref),
	manager_(wref.parent_manager())
{
}

sge::gui::widgets::parent_data::parent_data(
	manager &manager_)
: 
	widget_(0),
	manager_(manager_)
{
}

sge::gui::widgets::base *sge::gui::widgets::parent_data::parent_widget() const 
{ 
	return widget_; 
}

sge::gui::manager &sge::gui::widgets::parent_data::parent_manager() const 
{ 
	return manager_; 
}

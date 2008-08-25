#include <sge/gui/layout.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/iostream.hpp>

sge::gui::layout::layout(widgets::container &w)
	: w(w)
{
}

void sge::gui::layout::changed()
{
	sge::cerr << "layout: changed\n";

	// if size policy is fixed or it is a top level widget with dynamic size,
	// then the environment is "safe" and we can update without breaking the
	// layout of other widgets
	if (connected_widget().size_policy() == size_policy::fixed || 
		  !connected_widget().parent_widget())
	{
		sge::cerr << "layout: size_policy is fixed or we have a top level widget, so update\n";
		update();
		return;
	}

	// size policy is not fixed, so propagate event upwards until we get to a widget which
	// is fixed
	sge::cerr << "layout: propagaging changed event to upper layouts\n";
	connected_widget().layout()->changed();
}

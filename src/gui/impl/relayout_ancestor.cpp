#include <sge/gui/impl/relayout_ancestor.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>


void
sge::gui::impl::relayout_ancestor(
	sge::gui::widget::base &_widget
)
{
	sge::rucksack::widget::optional_ref layout(
		_widget.layout()
	);

	// TODO: Do this differently!
	while(
		layout.get_unsafe().parent().has_value()
	)
		layout =
			layout.get_unsafe().parent();

	layout.get_unsafe().relayout();
}

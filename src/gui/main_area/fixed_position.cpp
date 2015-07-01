#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/fixed_position.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>


sge::gui::main_area::fixed_position::fixed_position(
	sge::gui::widget::base &_widget,
	sge::rucksack::vector const _position
)
:
	sge::gui::main_area::base(),
	widget_(
		_widget
	),
	minimum_size_(
		widget_
	)
{
	minimum_size_.layout().position(
		_position
	);

	this->relayout();
}

sge::gui::main_area::fixed_position::~fixed_position()
{
}

void
sge::gui::main_area::fixed_position::relayout()
{
	minimum_size_.layout().relayout();
}

sge::gui::widget::base &
sge::gui::main_area::fixed_position::widget()
{
	return
		widget_;
}

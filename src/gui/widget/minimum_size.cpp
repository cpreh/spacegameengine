#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>


sge::gui::widget::minimum_size::minimum_size(
	sge::gui::widget::base &_widget
)
:
	sge::gui::widget::dummy(),
	layout_(
		_widget.layout()
	)
{
}

sge::gui::widget::minimum_size::~minimum_size()
{
}

sge::rucksack::widget::base &
sge::gui::widget::minimum_size::layout()
{
	return
		layout_;
}

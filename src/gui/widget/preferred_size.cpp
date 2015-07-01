#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/preferred_size.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>


sge::gui::widget::preferred_size::preferred_size(
	sge::rucksack::dim const &_area
)
:
	sge::gui::widget::dummy(),
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::preferred_size{
				_area.w()
			},
			sge::rucksack::preferred_size{
				_area.h()
			}
		}
	}
{
}

sge::gui::widget::preferred_size::~preferred_size()
{
}

sge::rucksack::widget::base &
sge::gui::widget::preferred_size::layout()
{
	return
		layout_;
}

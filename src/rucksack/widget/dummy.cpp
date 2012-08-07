#include <sge/rucksack/widget/dummy.hpp>

sge::rucksack::widget::dummy::dummy(
	sge::rucksack::axis_policy2 const &_axis_policy)
:
	widget::base(
		widget::optional_parent()),
	axis_policy_(
		_axis_policy),
	position_(),
	size_()
{
}

void
sge::rucksack::widget::dummy::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::dummy::position(
	sge::rucksack::vector const &_position)
{
	position_ =
		_position;
}

sge::rucksack::dim const
sge::rucksack::widget::dummy::size() const
{
	return size_;
}

sge::rucksack::vector const
sge::rucksack::widget::dummy::position() const
{
	return position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::dummy::axis_policy() const
{
	return axis_policy_;
}

void
sge::rucksack::widget::dummy::relayout()
{
}

sge::rucksack::widget::dummy::~dummy()
{
}

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>


sge::rucksack::widget::minimum_size::minimum_size(
	sge::rucksack::widget::base &_child
)
:
	sge::rucksack::widget::base(
		sge::rucksack::widget::optional_parent()
	),
	child_(
		_child
	)
{
}

void
sge::rucksack::widget::minimum_size::size(
	sge::rucksack::dim const &
)
{
}

void
sge::rucksack::widget::minimum_size::position(
	sge::rucksack::vector const &_position
)
{
	child_.position(
		_position
	);
}

sge::rucksack::dim const
sge::rucksack::widget::minimum_size::size() const
{
	return
		child_.size();
}

sge::rucksack::vector const
sge::rucksack::widget::minimum_size::position() const
{
	return
		child_.position();
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::minimum_size::axis_policy() const
{
	return
		child_.axis_policy();
}

void
sge::rucksack::widget::minimum_size::relayout()
{
	sge::rucksack::axis_policy2 const policy(
		child_.axis_policy()
	);

	child_.size(
		sge::rucksack::dim(
			policy.x().minimum_size(),
			policy.y().minimum_size()
		)
	);

	child_.relayout();
}

sge::rucksack::widget::minimum_size::~minimum_size()
{
}

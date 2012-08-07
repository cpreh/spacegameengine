#include <sge/rucksack/widget/box/child_information.hpp>

sge::rucksack::widget::box::child_information::child_information()
:
	alignment_(),
	size_()
{
}

sge::rucksack::widget::box::child_information::child_information(
	sge::rucksack::alignment::type const _alignment,
	sge::rucksack::dim const &_size)
:
	alignment_(
		_alignment),
	size_(
		_size)
{
}

sge::rucksack::alignment::type
sge::rucksack::widget::box::child_information::alignment() const
{
	return alignment_;
}

sge::rucksack::dim const &
sge::rucksack::widget::box::child_information::size() const
{
	return size_;
}

void
sge::rucksack::widget::box::child_information::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}

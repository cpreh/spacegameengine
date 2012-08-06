#include <sge/rucksack/widget/master_and_slaves.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/clog.hpp>


sge::rucksack::widget::master_and_slaves::master_and_slaves(
	sge::rucksack::padding const &_padding)
:
	widget::base(
		widget::optional_parent()),
	surrounding_box_(
		sge::rucksack::axis::x,
		sge::rucksack::aspect(
			1,
			1)),
	master_pane_(
		0),
	enumeration_(
		_padding,
		sge::rucksack::aspect(
			1,
			1)),
	position_(),
	size_()
{
	surrounding_box_.push_back_child(
		enumeration_,
		sge::rucksack::alignment::center);
}

void
sge::rucksack::widget::master_and_slaves::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::master_and_slaves::position(
	sge::rucksack::vector const &_position)
{
	position_ =
		_position;
}

sge::rucksack::dim const
sge::rucksack::widget::master_and_slaves::size() const
{
	return
		size_;
}

sge::rucksack::vector const
sge::rucksack::widget::master_and_slaves::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::master_and_slaves::axis_policy() const
{
	return
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					!master_pane_
					?
						0
					:
						master_pane_->axis_policy().x().minimum_size()),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					true)),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					!master_pane_
					?
						0
					:
						master_pane_->axis_policy().y().minimum_size()),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					true)),
			sge::rucksack::aspect(
				1,
				1));
}

void
sge::rucksack::widget::master_and_slaves::relayout()
{
	surrounding_box_.position(
		this->position());
	surrounding_box_.size(
		this->size());
	surrounding_box_.relayout();
}

void
sge::rucksack::widget::master_and_slaves::master_pane(
	widget::base &_master_pane)
{
	if(master_pane_)
		surrounding_box_.pop_front_child();
	surrounding_box_.push_front_child(
		_master_pane,
		sge::rucksack::alignment::center);
	master_pane_ =
		&_master_pane;
}

void
sge::rucksack::widget::master_and_slaves::push_back_child(
	widget::base &_child)
{
	enumeration_.push_back_child(
		_child);
}

sge::rucksack::widget::master_and_slaves::~master_and_slaves()
{
}

#include <sge/rucksack/widget/base.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>

sge::rucksack::widget::base::~base()
{
	if(parent_)
		parent_->child_destroyed(
			*this);
}

sge::rucksack::widget::base::base(
	sge::rucksack::widget::optional_parent const &_parent)
:
	parent_(
		_parent)
{
}

sge::rucksack::rect const
sge::rucksack::widget::base::area() const
{
	return
		sge::rucksack::rect(
			this->position(),
			this->size());
}

void
sge::rucksack::widget::base::parent(
	sge::rucksack::widget::optional_parent const &_parent)
{
	parent_ = _parent;
}

sge::rucksack::widget::optional_parent const &
sge::rucksack::widget::base::parent() const
{
	return parent_;
}

void
sge::rucksack::widget::base::child_destroyed(
	base &)
{
}

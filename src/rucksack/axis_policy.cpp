#include <sge/rucksack/axis_policy.hpp>

sge::rucksack::axis_policy::axis_policy(
	sge::rucksack::minimum_size const &_minimum_size,
	sge::rucksack::preferred_size const &_preferred_size,
	sge::rucksack::is_expanding const &_is_expanding)
:
	minimum_size_(
		_minimum_size.get()),
	preferred_size_(
		_preferred_size.get()),
	is_expanding_(
		_is_expanding.get())
{
}

sge::rucksack::scalar
sge::rucksack::axis_policy::minimum_size() const
{
	return minimum_size_;
}

sge::rucksack::optional_scalar
sge::rucksack::axis_policy::preferred_size() const
{
	return preferred_size_;
}

bool
sge::rucksack::axis_policy::is_expanding() const
{
	return is_expanding_;
}

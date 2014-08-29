#include <sge/rucksack/axis.hpp>
#include <sge/src/rucksack/flip_axis.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::rucksack::axis
sge::rucksack::flip_axis(
	sge::rucksack::axis const _axis
)
{
	switch(
		_axis
	)
	{
	case sge::rucksack::axis::x:
		return
			sge::rucksack::axis::y;
	case sge::rucksack::axis::y:
		return
			sge::rucksack::axis::x;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

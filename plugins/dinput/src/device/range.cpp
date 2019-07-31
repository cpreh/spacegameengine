//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/range.hpp>


sge::dinput::device::range::range(
	LONG const _min,
	LONG const _max
)
:
	min_(
		_min
	),
	max_(
		_max
	)
{
}

LONG
sge::dinput::device::range::min() const
{
	return
		min_;
}

LONG
sge::dinput::device::range::max() const
{
	return
		max_;
}

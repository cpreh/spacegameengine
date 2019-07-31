//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/pair.hpp>
#include <sge/x11input/device/valuator/value.hpp>


sge::x11input::device::valuator::pair::pair(
	sge::x11input::device::valuator::index const _index,
	sge::x11input::device::valuator::value const _value
)
:
	index_{
		_index
	},
	value_{
		_value
	}
{
}

sge::x11input::device::valuator::index
sge::x11input::device::valuator::pair::index() const
{
	return
		index_;
}

sge::x11input::device::valuator::value
sge::x11input::device::valuator::pair::value() const
{
	return
		value_;
}

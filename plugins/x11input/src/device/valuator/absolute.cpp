//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/device/valuator/absolute.hpp>
#include <sge/x11input/device/valuator/value.hpp>


sge::x11input::device::valuator::absolute::absolute(
	sge::x11input::device::valuator::value const _previous
)
:
	previous_{
		_previous
	}
{
}

sge::x11input::device::valuator::value
sge::x11input::device::valuator::absolute::previous() const
{
	return
		previous_;
}

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/relative.hpp>


sge::x11input::device::valuator::relative::relative()
:
	accu_{
		0.
	}
{
}

sge::x11input::device::valuator::relative::relative(
	sge::x11input::device::valuator::accu const _accu
)
:
	accu_{
		_accu
	}
{
}

sge::x11input::device::valuator::accu
sge::x11input::device::valuator::relative::accu() const
{
	return
		accu_;
}

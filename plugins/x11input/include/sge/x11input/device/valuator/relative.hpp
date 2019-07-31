//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_RELATIVE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_RELATIVE_HPP_INCLUDED

#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/relative_fwd.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

class relative
{
public:
	relative();

	explicit
	relative(
		sge::x11input::device::valuator::accu
	);

	sge::x11input::device::valuator::accu
	accu() const;
private:
	sge::x11input::device::valuator::accu accu_;
};

}
}
}
}

#endif

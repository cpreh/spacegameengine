//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ABSOLUTE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ABSOLUTE_HPP_INCLUDED

#include <sge/x11input/device/valuator/absolute_fwd.hpp>
#include <sge/x11input/device/valuator/value.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

class absolute
{
public:
	explicit
	absolute(
		sge::x11input::device::valuator::value
	);

	[[nodiscard]]
	sge::x11input::device::valuator::value
	previous() const;
private:
	sge::x11input::device::valuator::value previous_;
};

}
}
}
}

#endif

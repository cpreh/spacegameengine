//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_EVENT_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_EVENT_HPP_INCLUDED

#include <sge/evdev/device/event_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

class event
{
public:
	explicit
	event(
		input_event const &
	);

	input_event const &
	get() const;
private:
	input_event event_;
};

}
}
}

#endif

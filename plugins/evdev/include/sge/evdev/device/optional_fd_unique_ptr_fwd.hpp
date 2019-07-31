//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_OPTIONAL_FD_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_OPTIONAL_FD_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

typedef
fcppt::optional::object<
	sge::evdev::device::fd_unique_ptr
>
optional_fd_unique_ptr;

}
}
}

#endif

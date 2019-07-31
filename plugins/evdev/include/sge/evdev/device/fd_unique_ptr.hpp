//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_FD_UNIQUE_PTR_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_FD_UNIQUE_PTR_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

typedef
fcppt::unique_ptr<
	sge::evdev::device::fd
>
fd_unique_ptr;

}
}
}

#endif

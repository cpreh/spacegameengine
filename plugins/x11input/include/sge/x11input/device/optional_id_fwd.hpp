//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_OPTIONAL_ID_FWD_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_OPTIONAL_ID_FWD_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge
{
namespace x11input
{
namespace device
{

typedef fcppt::optional::object<sge::x11input::device::id> optional_id;

}
}
}

#endif

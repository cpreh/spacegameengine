//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_INFO_CONST_OPTIONAL_REF_FWD_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CONST_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <fcppt/optional/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::info
{

using const_optional_ref = fcppt::optional::reference<XIDeviceInfo const>;

}

#endif

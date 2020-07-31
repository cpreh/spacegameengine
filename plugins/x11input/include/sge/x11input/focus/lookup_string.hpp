//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_FOCUS_LOOKUP_STRING_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_LOOKUP_STRING_HPP_INCLUDED

#include <sge/x11input/focus/looked_up_string_fwd.hpp>
#include <sge/x11input/xim/context_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace focus
{

sge::x11input::focus::looked_up_string
lookup_string(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::x11input::xim::context const &,
	XIDeviceEvent const &
);

}
}
}

#endif

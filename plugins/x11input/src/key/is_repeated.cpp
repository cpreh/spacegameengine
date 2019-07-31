//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/key/is_repeated.hpp>
#include <sge/x11input/key/repeated.hpp>
#include <fcppt/bit/mask_c.hpp>
#include <fcppt/bit/test.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::key::repeated
sge::x11input::key::is_repeated(
	XIDeviceEvent const &_event
)
{
	return
		sge::x11input::key::repeated{
			fcppt::bit::test(
				_event.flags,
				fcppt::bit::mask_c<
					int,
					XIKeyRepeat
				>()
			)
		};
}

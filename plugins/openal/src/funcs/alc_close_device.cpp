//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/alc.hpp>
#include <sge/openal/funcs/alc_close_device.hpp>


bool
sge::openal::funcs::alc_close_device(
	ALCdevice &_device
)
{
	return
		::alcCloseDevice(
			&_device
		)
		!=
		ALC_FALSE
		;
}

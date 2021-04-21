//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/openal/alc.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_open_device.hpp>
#include <fcppt/text.hpp>


ALCdevice *
sge::openal::funcs::alc_open_device(
	ALCchar const *const _specifier
)
{
	ALCdevice *const result(
		::alcOpenDevice(
			_specifier
		)
	);

	SGE_OPENAL_CHECK_ALC_STATE(
		*result,
		FCPPT_TEXT("alcOpenDevice failed"),
		sge::audio::exception
	)

	if(
		result == nullptr
	)
	{
		throw
			sge::audio::exception{
				FCPPT_TEXT("AL device is null")
			};
	}

	return
		result;
}

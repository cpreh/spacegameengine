//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/sound/base_fwd.hpp>
#include <sge/audio/sound/do_pause.hpp>
#include <sge/audio/sound/pause.hpp>
#include <sge/audio/sound/pause_or_resume.hpp>
#include <sge/audio/sound/resume.hpp>


void
sge::audio::sound::pause_or_resume(
	sge::audio::sound::base &_sound,
	sge::audio::sound::do_pause const _do_pause
)
{
	if(
		_do_pause.get()
	)
	{
		sge::audio::sound::pause(
			_sound
		);
	}
	else
	{
		sge::audio::sound::resume(
			_sound
		);
	}
}

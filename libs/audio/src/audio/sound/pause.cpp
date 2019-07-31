//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/pause.hpp>
#include <sge/audio/sound/play_status.hpp>


void
sge::audio::sound::pause(
	sge::audio::sound::base &_sound
)
{
	if(
		_sound.status()
		==
		sge::audio::sound::play_status::playing
	)
		_sound.toggle_pause();
}

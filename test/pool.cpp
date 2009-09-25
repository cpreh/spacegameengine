/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/listener.hpp>
#include <sge/multi_loader.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <sge/cerr.hpp>
#include <sge/log/global.hpp>
#include <sge/log/logger.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <ostream>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <cmath>

int main()
try
{
	sge::log::global().activate_hierarchy(sge::log::level::debug);

	sge::filesystem::path const file_name(sge::config::media_path() / SGE_TEXT("ding.wav"));

	bool const streaming = false;

	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::multi_loader<
		sge::audio::loader,
		sge::audio::file,
		sge::audio::exception> loader(sys.plugin_manager());
	
	sge::audio::file_ptr const soundfile = loader.load(file_name);
	sge::audio::pool pool;

	sge::audio::sound_ptr sound = 
		streaming 
		? sys.audio_player()->create_stream_sound(soundfile)
		: sys.audio_player()->create_nonstream_sound(soundfile);

	sound->play(sge::audio::play_mode::loop);

	pool.add(sound,sge::audio::stop_mode::play_once);

	sge::time::timer t(sge::time::second(2));
	while (!pool.sounds_finished())
	{
		pool.update();
		if (t.update_b())
		{
			sge::cerr << SGE_TEXT("killing sound\n");
			sound.reset();
		}
	}
} catch (const sge::audio::exception &e) {
	sge::cerr << SGE_TEXT("audio exception caught: ") << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (const sge::exception &e) {
	sge::cerr << SGE_TEXT("Exception caught: ") << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (const std::exception &e) {
	std::cerr << "Exception caught: " << e.what() << '\n';
	return EXIT_FAILURE;
}

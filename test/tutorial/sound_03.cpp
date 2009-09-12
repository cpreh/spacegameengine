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
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>
#include <sge/multi_loader.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/config/media_path.hpp>
#include <sge/math/pi.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <exception>
#include <cmath>
#include <cstdlib>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::multi_loader<sge::audio::loader,sge::audio::file,sge::audio::exception> loader(sys.plugin_manager());

	sge::audio::file_ptr const file(
		loader.load(
			sge::config::media_path() / SGE_TEXT("ding.wav")
		)
	);

	sge::audio::sound_ptr const sound = sys.audio_player()->create_nonstream_sound(file);

	sound->positional(true);
	sound->play(sge::audio::play_mode::loop);

	sge::time::timer frame_timer(sge::time::second(static_cast<sge::time::unit>(1)));
	sge::audio::unit const rpm = static_cast<sge::audio::unit>(1);
	sge::audio::unit const speed = static_cast<sge::audio::unit>(
		static_cast<sge::audio::unit>(2) * sge::math::pi<sge::audio::unit>() * rpm);
	while (true)
	{
		sge::audio::unit const angle = 
			static_cast<sge::audio::unit>(frame_timer.elapsed_frames() * speed);
		sound->pos(
			sge::audio::point(
				std::sin(angle),
				static_cast<sge::audio::unit>(0),
				std::cos(angle)));
		sound->update();
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}

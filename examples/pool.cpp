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
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/config/media_path.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/exception.hpp>
#include <sge/multi_loader.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <ostream>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <cmath>

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	fcppt::filesystem::path const file_name(
		sge::config::media_path()
		/ FCPPT_TEXT("ding.wav")
	);

	bool const streaming = false;

	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player)
		(
			sge::systems::audio_loader(
				sge::audio::loader_capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("wav")
				)
			)
		)
	);

	sge::audio::file_ptr const soundfile(
		sys.audio_loader().load(
			file_name
		)
	);

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
			fcppt::io::cerr << FCPPT_TEXT("killing sound\n");
			sound.reset();
		}
	}
}
catch(
	sge::audio::exception const &e
)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("audio exception caught: ")
		<< e.string()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}
catch(
	sge::exception const &e
)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("Exception caught: ")
		<< e.string()
		<< FCPPT_TEXT('\n');
	
	return EXIT_FAILURE;
}
catch(
	std::exception const &e
)
{
	std::cerr
		<< "Exception caught: "
		<< e.what()
		<< '\n';

	return EXIT_FAILURE;
}

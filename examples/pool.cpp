/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/audio/pool/object.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/config/media_path.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/exception.hpp>
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

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::audio_player_default()
		)
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

	sge::audio::pool::object pool(
		sge::audio::pool::gain_factor(
			static_cast<sge::audio::pool::gain_factor::value_type>(
				1)),
		sge::audio::pool::pitch_factor(
			static_cast<sge::audio::pool::pitch_factor::value_type>(
				1)));

	sge::audio::sound::base_ptr sound(
		sys.audio_player().create_nonpositional_stream(
			soundfile
		)
	);

	sound->play(
		sge::audio::sound::repeat::loop
	);

	pool.add(
		sound,
		sge::audio::pool::stop_mode::play_once
	);

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

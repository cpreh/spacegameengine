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


#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <exception>
#include <cstdlib>

int main()
try
{
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
				(
					FCPPT_TEXT("ogg")
				)
			)
		)
	);

	sge::audio::pool pool;

	{
		sge::audio::sound::base_ptr const sound_01(
			sys.audio_player()->create_nonpositional_stream(
				sys.audio_loader().load(
					sge::config::media_path() / FCPPT_TEXT("ding.wav")
				)
			)
		);

		sge::audio::sound::base_ptr const sound_02(
			sys.audio_player()->create_nonpositional_stream(
				sys.audio_loader().load(
					sge::config::media_path() / FCPPT_TEXT("siren.ogg")
				)
			)
		);

		pool.add(
			sound_01,
			sge::audio::stop_mode::play_once
		);

		pool.add(
			sound_02,
			sge::audio::stop_mode::play_once
		);

		sound_01->play(
			sge::audio::sound::repeat::once
		);

		sound_02->play(
			sge::audio::sound::repeat::once
		);
	}

	while (!pool.sounds_finished())
		pool.update();
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}

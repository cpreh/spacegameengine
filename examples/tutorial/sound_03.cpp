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
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/config/media_path.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cmath>
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
			)
		)
	);

	sge::audio::file_ptr const file(
		sys.audio_loader().load(
			sge::config::media_path()
			/ FCPPT_TEXT("ding.wav")
		)
	);

	sge::audio::sound::positional_ptr const sound(
		sys.audio_player()->create_positional_stream(
			file,
			sge::audio::sound::positional_parameters()
		)
	);

	sound->play(
		sge::audio::sound::repeat::loop
	);

	sge::time::timer frame_timer(
		sge::time::second(
			static_cast<
				sge::time::unit
			>(
				1
			)
		)
	);

	sge::audio::scalar const rpm(
		static_cast<
			sge::audio::scalar
		>(
			1
		)
	);

	sge::audio::scalar const speed(
		static_cast<
			sge::audio::scalar
		>(
			fcppt::math::twopi<
				sge::audio::scalar
			>()
			* rpm
		)
	);

	for(;;)
	{
		sge::audio::scalar const angle(
			static_cast<
				sge::audio::scalar
			>(
				frame_timer.elapsed_frames()
				*
				speed
			)
		);

		sound->position(
			sge::audio::vector(
				std::sin(angle),
				static_cast<sge::audio::scalar>(0),
				std::cos(angle)
			)
		);

		sound->update();
	}
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	std::cerr << e.what() << '\n';

	return EXIT_FAILURE;
}

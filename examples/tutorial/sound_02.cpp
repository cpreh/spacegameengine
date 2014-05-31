/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	sge::systems::instance<
		boost::mpl::vector2<
			sge::systems::with_audio_loader,
			sge::systems::with_audio_player
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::audio_player_default()
		)
		(
			sge::systems::audio_loader(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("wav")
						)
					}
				)
			)
		)
	);

	sge::audio::file_unique_ptr const file(
		sge::audio::load_exn(
			sys.audio_loader(),
			sge::config::media_path()
			/	FCPPT_TEXT("sounds")
			/ FCPPT_TEXT("ding.wav")
		)
	);

	sge::audio::sound::positional_unique_ptr const sound(
		sys.audio_player().create_positional_stream(
			*file,
			sge::audio::sound::positional_parameters()
		)
	);

	sound->play(
		sge::audio::sound::repeat::loop
	);

	sge::timer::basic<sge::timer::clocks::standard> frame_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			std::chrono::seconds(
				1)));

	sge::audio::scalar const rpm(
		static_cast<sge::audio::scalar>(
			1));

	sge::audio::scalar const speed(
		static_cast<sge::audio::scalar>(
			fcppt::math::twopi<sge::audio::scalar>() * rpm));

	for(;;)
	{
		sge::audio::scalar const angle(
			static_cast<sge::audio::scalar>(
				sge::timer::elapsed_fractional<sge::audio::scalar>(
					frame_timer) *
				speed));

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
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}

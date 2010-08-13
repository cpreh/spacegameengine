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
#include <sge/audio/exception.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/config/media_path.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/sleep.hpp>
#include <sge/log/global.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/time/sleep.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <ostream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

namespace
{
void
wait_for_input()
{
	fcppt::io::cout << FCPPT_TEXT("Please press enter to continue...\n");
	fcppt::string input;
	std::getline(
		fcppt::io::cin,
		input);
}
}

int main(int, char *[])
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	fcppt::filesystem::path const file_name = 
		sge::config::media_path() / 
		FCPPT_TEXT("ding.wav");

	fcppt::io::cout << FCPPT_TEXT("This is the sge sound example. We will now try to load the audio loader\n");
	wait_for_input();

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::parameterless::audio_player
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

	fcppt::io::cout << FCPPT_TEXT("Audio loader loaded\n");
	fcppt::io::cout << FCPPT_TEXT("We will now try to load a sound file\n");
	wait_for_input();

	sge::audio::file_ptr const soundfile = 
		sys.audio_loader().load(
			file_name);

	fcppt::io::cout << FCPPT_TEXT("Sound file loaded\n");
	fcppt::io::cout << FCPPT_TEXT("We will now try to create a nonstreaming buffer from it.\n");
	wait_for_input();

	sge::audio::buffer_ptr const buf = 
		sys.audio_player()->create_buffer(
			soundfile);

	fcppt::io::cout << FCPPT_TEXT("Buffer created\n");
	fcppt::io::cout << FCPPT_TEXT("We will now try to create a nonpositional source from it.\n");
	wait_for_input();
	
	sge::audio::sound::base_ptr const s = 
		buf->create_nonpositional();

	fcppt::io::cout << FCPPT_TEXT("Nonpositional source loaded\n");
	fcppt::io::cout << FCPPT_TEXT("You should hear a sound after pressing enter\n");
	wait_for_input();

	/*
	if (revolving)
	{
		sound->positional(true);
		sound->pos(
			sge::audio::vector(
				static_cast<sge::audio::scalar>(-1),
				static_cast<sge::audio::scalar>(0),
				static_cast<sge::audio::scalar>(0)));
	}
	*/
	s->play(
		sge::audio::sound::repeat::once);

	sge::time::timer frame_timer(
		sge::time::second(
			1));

	while (s->status() != sge::audio::sound::play_status::stopped)
		s->update();

	fcppt::io::cout << FCPPT_TEXT("Now we use the same sound, but create a positional source from it.\n");
	wait_for_input();

	sge::audio::sound::positional_ptr const ps = 
		buf->create_positional(
			sge::audio::sound::positional_parameters()
				.linear_velocity(
					sge::audio::vector::null())
				.position(
					sge::audio::vector::null())
				.rolloff(
					1));

	fcppt::io::cout << FCPPT_TEXT("Sound created at the origin, now we play it\n");
	wait_for_input();

	s->play(
		sge::audio::sound::repeat::once);

	while (ps->status() != sge::audio::sound::play_status::stopped)
		ps->update();

	fcppt::io::cout << FCPPT_TEXT("Now we reposition and play again\n");
	wait_for_input();

	ps->position(
		sge::audio::vector(
			-10000,
			0,
			0));

	s->play(
		sge::audio::sound::repeat::once);

	while (ps->status() != sge::audio::sound::play_status::stopped)
		ps->update();

	fcppt::io::cout << FCPPT_TEXT("Finished\n");
	wait_for_input();
} catch (sge::audio::exception const &e) {
	fcppt::io::cerr << FCPPT_TEXT("audio exception caught: ") << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
} catch (sge::exception const &e) {
	fcppt::io::cerr << FCPPT_TEXT("Exception caught: ") << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
} catch (std::exception const &e) {
	std::cerr << "Exception caught: " << e.what() << '\n';
	return EXIT_FAILURE;
}

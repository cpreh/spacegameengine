/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/buffer.hpp>
#include <sge/audio/buffer_scoped_ptr.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_scoped_ptr.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_scoped_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/positional_scoped_ptr.hpp>
#include <sge/config/media_path.hpp>
#include <sge/log/global.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::audio::file_unique_ptr
load_raw(
	boost::filesystem::path const &path,
	sge::audio::loader &audio_loader)
{
	boost::filesystem::ifstream raw_stream(
		path,
		std::ios::binary);

	typedef
	fcppt::container::raw_vector<char>
	raw_byte_container;

	raw_byte_container raw_bytes(
		(std::istreambuf_iterator<char>(
			raw_stream)),
		std::istreambuf_iterator<char>());

	return
		audio_loader.load_raw(
			boost::make_iterator_range(
				reinterpret_cast<unsigned char const *>(
					&(*raw_bytes.cbegin())),
				reinterpret_cast<unsigned char const *>(
					&(*raw_bytes.cend()))),
			sge::media::optional_extension());
}
}

namespace
{
void
wait_for_input()
{
	fcppt::io::cout()
		<< FCPPT_TEXT("Please press enter to continue...\n");
	fcppt::string input;
	std::getline(
		fcppt::io::cin(),
		input);
}

void
wait_for_sound(
	sge::audio::sound::base &_sound)
{
	while (_sound.status() != sge::audio::sound::play_status::stopped)
		_sound.update();
}
}

int
main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	boost::filesystem::path const
		file_name =
			sge::config::media_path() /
			FCPPT_TEXT("sounds") /
			FCPPT_TEXT("ding.wav"),
		streaming_file_name =
			sge::config::media_path() /
			FCPPT_TEXT("sounds") /
			FCPPT_TEXT("epoq.ogg");

	fcppt::io::cout()
		<< FCPPT_TEXT("This is the sge sound example. We will now try to load the audio loader\n");

	wait_for_input();

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::audio_player_default()
		)
		(
			sge::systems::audio_loader(
				sge::audio::loader_capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>
						(sge::media::extension(FCPPT_TEXT("wav")))
						(sge::media::extension(FCPPT_TEXT("ogg")))
				)
			)
		)
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("Audio loader loaded\n")
		<< FCPPT_TEXT("We will now try to load a sound file\n");

	wait_for_input();

	sge::audio::file_scoped_ptr const soundfile(
		load_raw(
			file_name,
			sys.audio_loader()));

	fcppt::io::cout()
		<< FCPPT_TEXT("Sound file loaded\n")
		<< FCPPT_TEXT("We will now try to create a nonstreaming buffer from it.\n");

	wait_for_input();

	sge::audio::buffer_scoped_ptr const buf(
		sys.audio_player().create_buffer(
			*soundfile));

	fcppt::io::cout()
		<< FCPPT_TEXT("Buffer created\n")
		<< FCPPT_TEXT("We will now try to create a nonpositional source from it.\n");

	wait_for_input();

	sge::audio::sound::base_scoped_ptr const sound(
		buf->create_nonpositional(
			sge::audio::sound::nonpositional_parameters()));

	fcppt::io::cout()
		<< FCPPT_TEXT("Nonpositional source loaded\n")
		<< FCPPT_TEXT("You should hear a sound after pressing enter\n");

	wait_for_input();

	sound->play(
		sge::audio::sound::repeat::once);

	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("Now we use the same sound, but create a positional source from it.\n");

	wait_for_input();

	sge::audio::sound::positional_scoped_ptr const positional_sound(
		buf->create_positional(
			sge::audio::sound::positional_parameters()
				.linear_velocity(
					sge::audio::vector::null())
				.position(
					sge::audio::vector::null())));

	fcppt::io::cout()
		<< FCPPT_TEXT("Sound created at the origin, now we play it\n");

	wait_for_input();

	sound->play(
		sge::audio::sound::repeat::once);

	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("Now we reposition and play again\nYou should hear the sound coming from the _left_ now.\n");

	wait_for_input();

	positional_sound->position(
		sge::audio::vector(
			-2,
			0,
			0));

	positional_sound->play(
		sge::audio::sound::repeat::once);

	wait_for_sound(
		*positional_sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("Back to the nonpositional sound. We now try to lower the volume globally. Playing at 100% volume...\n");

	wait_for_input();

	sound->play(
		sge::audio::sound::repeat::once);
	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("Now 50% volume...\n");

	wait_for_input();

	sys.audio_player().gain(
		static_cast<sge::audio::scalar>(0.5));

	sound->play(
		sge::audio::sound::repeat::once);
	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("Now 25% volume...\n");

	wait_for_input();

	sys.audio_player().gain(
		static_cast<sge::audio::scalar>(0.25));

	sound->play(
		sge::audio::sound::repeat::once);
	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("And finally 0% volume...\n");

	wait_for_input();

	sys.audio_player().gain(
		static_cast<sge::audio::scalar>(0.0));

	sound->play(
		sge::audio::sound::repeat::once);
	wait_for_sound(
		*sound);

	sys.audio_player().gain(
		static_cast<sge::audio::scalar>(1.0));

	fcppt::io::cout()
		<< FCPPT_TEXT("Let's try changing the sound pitch now...You'll hear the sound with a 50% pitch now.\n");

	wait_for_input();

	sound->pitch(
		static_cast<sge::audio::scalar>(
			0.5));

	sound->play(
		sge::audio::sound::repeat::once);
	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("Now with 150% pitch...\n");

	wait_for_input();

	sound->pitch(
		static_cast<sge::audio::scalar>(
			1.5));

	sound->play(
		sge::audio::sound::repeat::once);
	wait_for_sound(
		*sound);

	fcppt::io::cout()
		<< FCPPT_TEXT("On to streaming sounds, we'll now create a positional streaming sound...\n");

	wait_for_input();

	sge::audio::sound::positional_scoped_ptr const streaming_positional_sound(
		sys.audio_player().create_positional_stream(
			*sys.audio_loader().load(
				streaming_file_name),
			sge::audio::sound::positional_parameters()
				.linear_velocity(
					sge::audio::vector::null())
				.position(
					sge::audio::vector(
						-2000,
						0,
						0))));

	fcppt::io::cout()
		<< FCPPT_TEXT("Streaming sound created.\nWe'll now play it for 10 seconds.\n");

	wait_for_input();

	streaming_positional_sound->play(
		sge::audio::sound::repeat::once);

	streaming_positional_sound->position(
		sge::audio::vector(
			-2000,
			0,
			0));

	sge::timer::basic<sge::timer::clocks::standard> frame_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			boost::chrono::seconds(
				10)));

	while(
		streaming_positional_sound->status() != sge::audio::sound::play_status::stopped
		&& !frame_timer.expired())
		streaming_positional_sound->update();
	streaming_positional_sound->stop();

	fcppt::io::cout()
		<< FCPPT_TEXT("Finished\n");
	wait_for_input();

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

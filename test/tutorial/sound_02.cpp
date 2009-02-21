#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/path.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

namespace
{
// replace both!
sge::path const sound_file_01(SGE_TEXT("file 01"));
sge::path const sound_file_02(SGE_TEXT("file 02"));
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::audio::multi_loader loader(sys.plugin_manager());

	sge::audio::pool_ptr const pool(sys.audio_player()->create_pool());

	{
		sge::audio::sound_ptr const sound_01 = 
			sys.audio_player()->create_nonstream_sound(
				load.load(sound_file_01));

		sge::audio::sound_ptr const sound_02 = 
			sys.audio_player()->create_stream_sound(
				load.load(sound_file_02));

		pool->add(sound_01,true);
		pool->add(sound_02,true);

		sound_01->play(sge::audio::play_mode::once);
		sound_02->play(sge::audio::play_mode::once);
	}

	while (!pool->sounds_finished())
		pool->update();
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}

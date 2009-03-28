#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <exception>
#include <cstdlib>

namespace
{
// replace both!
sge::filesystem::path const sound_file_01(SGE_TEXT("file 01"));
sge::filesystem::path const sound_file_02(SGE_TEXT("file 02"));
}

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::audio::multi_loader loader(sys.plugin_manager());

	sge::audio::pool pool;

	{
		sge::audio::sound_ptr const sound_01 = 
			sys.audio_player()->create_nonstream_sound(
				loader.load(sound_file_01));

		sge::audio::sound_ptr const sound_02 = 
			sys.audio_player()->create_stream_sound(
				loader.load(sound_file_02));

		pool.add(sound_01, sge::audio::stop_mode::play_once);
		pool.add(sound_02, sge::audio::stop_mode::play_once);

		sound_01->play(sge::audio::play_mode::once);
		sound_02->play(sge::audio::play_mode::once);
	}

	while (!pool.sounds_finished())
		pool.update();
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

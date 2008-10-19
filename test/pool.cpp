#include <sge/audio/multi_loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/listener.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/context.hpp>
#include <sge/media.hpp>
#include <sge/math/constants.hpp>
#include <sge/su.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/sleep.hpp>
#include <sge/log/headers.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/time/sleep.hpp>
#include <sge/iconv.hpp>
#include <ostream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>

int main(int, char *[])
try
{
	sge::log::global().activate_hierarchy(sge::log::level::debug);

  sge::path file_name(sge::media_path() / SGE_TEXT("ding.wav"));

	bool const streaming = false;

	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::audio::multi_loader loader(sys.plugin_manager());
	
	sge::audio::file_ptr const soundfile = loader.load(file_name);
	sge::audio::pool_ptr const pool = sys.audio_player()->create_pool();

	{
		sge::audio::sound_ptr const sound = 
			streaming 
			? sys.audio_player()->create_stream_sound(soundfile)
			: sys.audio_player()->create_nonstream_sound(soundfile);

		pool->add(sound,true);

		sound->play(sge::audio::play_mode::once);
	}

	while (!pool->sounds_finished())
		pool->update();
} catch (const sge::audio::exception &e) {
	sge::cerr << SGE_TEXT("audio exception caught: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (const sge::exception &e) {
	sge::cerr << SGE_TEXT("Exception caught: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (const std::exception &e) {
	std::cerr << "Exception caught: " << e.what() << '\n';
	return EXIT_FAILURE;
}

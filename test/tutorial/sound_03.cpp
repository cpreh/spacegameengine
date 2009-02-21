#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/path.hpp>
#include <sge/math/constants.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cmath>
#include <cstdlib>

namespace 
{
// replace!
sge::path const sound_file(SGE_TEXT("your path here"));
}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::audio::multi_loader loader(sys.plugin_manager());

	sge::audio::file_ptr const file = loader.load(sound_file);

	sge::audio::sound_ptr const sound = sys.audio_player()->create_nonstream_sound(file);

	sound->positional(true);
	sound->play(sge::audio::play_mode::loop);

	sge::time::timer frame_timer(sge::time::second(static_cast<sge::time::unit>(1)));
	sge::audio::unit const rpm = static_cast<sge::audio::unit>(1);
	sge::audio::unit const speed = static_cast<sge::audio::unit>(
		static_cast<sge::audio::unit>(2) * sge::math::pi<sge::audio::unit>() * rpm);
	while (true)
	{
		sge::audio::unit const angle = 
			static_cast<sge::audio::unit>(frame_timer.elapsed_frames() * speed);
		sound->pos(
			sge::audio::point(
				std::sin(angle),
				static_cast<sge::audio::unit>(0),
				std::cos(angle)));
		sound->update();
	}
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

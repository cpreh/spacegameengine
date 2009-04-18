#include <sge/audio/multi_loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/listener.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/context.hpp>
#include <sge/config/media_path.hpp>
#include <sge/math/constants.hpp>
#include <sge/exception.hpp>
#include <sge/cerr.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/sleep.hpp>
#include <sge/log/headers.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/time/sleep.hpp>
#include <sge/iconv.hpp>
#include <boost/program_options.hpp>
#include <ostream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>

int main(int argc, char *argv[])
try
{
	sge::log::global().activate_hierarchy(sge::log::level::debug);

	namespace po = boost::program_options;
	po::options_description desc("allowed options");

	std::string file_name_prog_options;
	bool revolving,streaming;
	sge::audio::unit speed;

	// FIXME: can't we use wstring here too?
	desc.add_options()
	("help",
	"produce help message")
	("file",
	po::value<std::string>(&file_name_prog_options),
	"sets the sound file name")
	("revolving",
	po::value<bool>(&revolving)->default_value(true),
	"does the sound revolve around the player")
	("speed",
	po::value<sge::audio::unit>(&speed)->default_value(static_cast<sge::audio::unit>(1)),
	"speed of the sound in percent of 2*pi per second")
	("streaming",
	po::value<bool>(&streaming)->default_value(false),
	"stream sound or not");

	po::variables_map vm;
	po::store(po::parse_command_line(argc,argv,desc),vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << "\n";
		 return EXIT_SUCCESS;
	}

	sge::filesystem::path file_name(sge::iconv(file_name_prog_options));
	if (file_name.empty())
		file_name = sge::config::media_path() / SGE_TEXT("ding.wav");

	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::audio::multi_loader loader(sys.plugin_manager());
	
	sge::audio::file_ptr const soundfile = loader.load(file_name);

	sge::audio::sound_ptr const sound = 
		streaming 
		? sys.audio_player()->create_stream_sound(soundfile)
		: sys.audio_player()->create_nonstream_sound(soundfile);

	sys.audio_player()->listener().pos(
		sge::audio::point(
			static_cast<sge::audio::unit>(0),
			static_cast<sge::audio::unit>(0),
			static_cast<sge::audio::unit>(0)));
	if (revolving)
	{
		sound->positional(true);
		sound->pos(
			sge::audio::point(
				static_cast<sge::audio::unit>(-1),
				static_cast<sge::audio::unit>(0),
				static_cast<sge::audio::unit>(0)));
	}
	sound->play(sge::audio::play_mode::once);

	sge::time::timer frame_timer(sge::time::second(1));
	while (sound->status() != sge::audio::sound_status::stopped)
	{
		if (revolving)
		{
			sge::audio::unit const angle = 
				static_cast<sge::audio::unit>(
					frame_timer.elapsed_frames() * (2 * sge::math::PI * speed));
			sound->pos(
				sge::audio::point(
					std::sin(angle),
					static_cast<sge::audio::unit>(0),
					std::cos(angle)));
		}

		sound->update();
		sge::time::sleep(sge::time::millisecond(250));
	}
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

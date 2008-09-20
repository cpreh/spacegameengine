#include "mpeg_file.hpp"
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
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
#include <sge/systems.hpp>
#include <sge/init.hpp>
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

	sge::audio::file_ptr const soundfile(new sge::mad::mpeg_file(SGE_TEXT("/mnt/extern/musik/misc/29 - the notwist - good lies.mp3")));

	namespace po = boost::program_options;
  po::options_description desc("allowed options");

	std::string file_name_prog_options;
	bool revolving,streaming;
	sge::space_unit speed;

	// FIXME: can't we use wstring here too?
  desc.add_options()
      ("help",
        "produce help message")
      ("file",
        po::value<std::string>(&file_name_prog_options),
        "sets the sound file name")
      ("revolving",
        po::value<bool>(&revolving)->default_value(false),
        "does the sound revolve around the player")
      ("speed",
        po::value<sge::space_unit>(&speed)->default_value(sge::su(1)),
        "speed of the sound in percent of 2*pi per second")
      ("streaming",
        po::value<bool>(&streaming)->default_value(true),
        "stream sound or not");

  po::variables_map vm;
  po::store(po::parse_command_line(argc,argv,desc),vm);
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cout << desc << "\n";
    return EXIT_SUCCESS;
  }

  sge::string file_name(sge::iconv(file_name_prog_options));
	if (file_name.empty())
		file_name = sge::media_path().string()+SGE_TEXT("/ding.wav");

	sge::systems sys;
	sys.init<sge::init::audio_player>();
	
	//sge::audio::file_ptr const soundfile(new sge::mad::mpeg_file(file_name));

	sge::audio::sound_ptr const sound = 
		streaming 
		? sys.audio_player->create_stream_sound(soundfile)
		: sys.audio_player->create_nonstream_sound(soundfile);

	sys.audio_player->listener_pos(sge::audio::sound_pos(0,0,0));
	if (revolving)
	{
		sound->positional(true);
		sound->pos(sge::audio::sound_pos(-1,0,0));
	}
	sound->play(sge::audio::play_mode::loop);

	sge::time::timer frame_timer(sge::time::second(static_cast<sge::time::unit>(1)));
	while (true)
	{
		if (revolving)
		{
			sge::space_unit angle = 
				sge::su(
					frame_timer.elapsed_frames() * (2 * sge::math::PI * speed));
			sound->pos(sge::audio::sound_pos(std::sin(angle),0,std::cos(angle)));
		}
		sys.audio_player->update();
	}
	
} catch (const sge::exception &e) {
	sge::cerr << SGE_TEXT("Exception caught: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (const std::exception &e) {
	std::cerr << "Exception caught: " << e.what() << '\n';
	return EXIT_FAILURE;
}

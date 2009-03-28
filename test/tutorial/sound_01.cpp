#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/cerr.hpp>
#include <exception>
#include <cstdlib>

namespace 
{
// replace!
sge::filesystem::path const sound_file(SGE_TEXT("your path here"));
}

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::parameterless::audio_player));

	sge::audio::multi_loader loader(sys.plugin_manager());

	sge::audio::file_ptr const file = loader.load(sound_file);

	sge::audio::sound_ptr const sound = sys.audio_player()->create_nonstream_sound(file);

	sound->play(sge::audio::play_mode::loop);

	while (true)
		sound->update();
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

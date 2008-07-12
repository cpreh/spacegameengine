#include <sge/audio/loader/loader.hpp>
#include <sge/audio/player/player.hpp>
#include <sge/audio/player/sound.hpp>
#include <sge/plugin_manager.hpp>
#include <sge/media.hpp>
#include <sge/math/constants.hpp>
#include <sge/util.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/second.hpp>
#include <ostream>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <cmath>

int main()
try
{
	sge::plugin_manager pm;
	const sge::plugin<sge::audio::player>::ptr_type audio_player_plugin = pm.get_plugin<sge::audio::player>().load();
	sge::shared_ptr<sge::audio::player> audio_player(audio_player_plugin->get()());

	typedef std::vector< sge::plugin_manager::plugin_context<sge::audio::loader> > plugin_vector;
	plugin_vector audio_plugins;
	std::copy(pm.begin<sge::audio::loader>(),pm.end<sge::audio::loader>(),std::back_inserter(audio_plugins));

	typedef std::vector<sge::plugin_manager::plugin_context<sge::audio::loader>::ptr_type> loaded_plugins_vector;
	loaded_plugins_vector loaded;

	typedef std::vector<sge::audio::loader_ptr> audio_loader_vector;
	audio_loader_vector loaders;

	sge::shared_ptr<sge::audio::file> soundfile;
	for (plugin_vector::iterator i = audio_plugins.begin(); i != audio_plugins.end(); ++i)
	{
		sge::plugin_manager::plugin_context<sge::audio::loader>::ptr_type np = i->load();
		loaded.push_back(np);
		sge::shared_ptr<sge::audio::loader> j(np->get()());
		loaders.push_back(j);
		const sge::path path = sge::media_path() / SGE_TEXT("ding.wav");
		//const std::string path = "/home/philipp/musik/queen_greatest_hits_iii/queen_you_dont_fool_me.ogg";
		if (j->is_valid_file(path))
			soundfile = j->load(path);
	}
	if(!soundfile)
		throw std::runtime_error("ding.wav not found!");
	const sge::audio::sound_ptr soundleft = audio_player->create_nonstream_sound(soundfile),
	                            soundright = audio_player->create_nonstream_sound(soundfile);

	audio_player->listener_pos(sge::math::vector3(0,0,0));
	soundleft->positional(true);
	soundleft->pos(sge::math::vector3(-1,0,0));
	soundright->positional(true);
	soundleft->pos(sge::math::vector3(1,0,0));
	soundleft->play(true);
	sge::sleep(1);
	//soundright->play(true);	

	//sge::sleep(20000);

	sge::time::timer frame_timer(sge::time::second(static_cast<sge::time::unit>(1)));
	while (true)
	{
		sge::space_unit angle = frame_timer.elapsed_frames() * 2 * sge::math::PI;
		soundleft->pos(sge::math::vector3(std::sin(angle),0,std::cos(angle)));
		audio_player->update();
	}
	
} catch (const sge::exception &e) {
	sge::cerr << SGE_TEXT("Exception caught: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (const std::exception &e) {
	sge::cerr << SGE_TEXT("Exception caught: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}

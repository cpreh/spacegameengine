#include <cmath>
#include <iostream>
#include <stdexcept>
#include <sge/audio/audio_loader/audio_loader.hpp>
#include <sge/audio/audio_player/audio_player.hpp>
#include <sge/audio/audio_player/sound.hpp>
#include <sge/plugin_manager.hpp>
#include <sge/media.hpp>
#include <sge/timer.hpp>
#include <sge/math/constants.hpp>

int main()
try
{
	sge::plugin_manager pm;
	const sge::plugin<sge::audio_player>::ptr_type audio_player_plugin = pm.get_plugin<sge::audio_player>().load();
	sge::shared_ptr<sge::audio_player> audio_player(audio_player_plugin->get()());

	typedef std::vector< sge::plugin_manager::plugin_context<sge::audio_loader> > plugin_vector;
	plugin_vector audio_plugins;
	std::copy(pm.begin<sge::audio_loader>(),pm.end<sge::audio_loader>(),std::back_inserter(audio_plugins));

	typedef std::vector<sge::plugin_manager::plugin_context<sge::audio_loader>::ptr_type> loaded_plugins_vector;
	loaded_plugins_vector loaded;

	typedef std::vector< sge::shared_ptr<sge::audio_loader> > audio_loader_vector;
	audio_loader_vector loaders;

	sge::shared_ptr<sge::audio_file> soundfile;
	for (plugin_vector::iterator i = audio_plugins.begin(); i != audio_plugins.end(); ++i)
	{
		sge::plugin_manager::plugin_context<sge::audio_loader>::ptr_type np = i->load();
		loaded.push_back(np);
		sge::shared_ptr<sge::audio_loader> j(np->get()());
		loaders.push_back(j);
		const std::string path = sge::media_path()+"ding.wav";
		//const std::string path = "/home/philipp/musik/queen_greatest_hits_iii/queen_you_dont_fool_me.ogg";
		if (j->is_valid_file(path))
			soundfile = j->load(path);
	}
	if(!soundfile)
		throw std::runtime_error("ding.wav not found!");
	sge::shared_ptr<sge::sound> soundleft = audio_player->create_nonstream_sound(soundfile);
	sge::shared_ptr<sge::sound> soundright = audio_player->create_nonstream_sound(soundfile);

	audio_player->listener_pos(sge::math::vector3(0,0,0));
	soundleft->positional(true);
	soundleft->pos(sge::math::vector3(-1,0,0));
	soundright->positional(true);
	soundleft->pos(sge::math::vector3(1,0,0));
	soundleft->play(true);
	sleep(1);
	soundright->play(true);
	

	sleep(20);

	/*
	sge::timer frame_timer(1000);
	while (true)
	{
		sge::space_unit angle = frame_timer.elapsed_frames() * 2 * sge::math::PI;
		sound->pos(sge::math::vector3(std::sin(angle),0,std::cos(angle)));
		audio_player->update();
	}
	*/
} catch (const std::exception &e) {
	std::cerr << "Exception caught: " << e.what() << "\n";
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/bind.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include "../src/math/constants.hpp"
#include "../src/texture/default_creator.hpp"
#include "../src/texture/util.hpp"
#include "../src/texture/default_creator_impl.hpp"
#include "../src/texture/no_fragmented_texture.hpp"
#include "../src/plugin_manager.hpp"
#include "../src/renderer/scoped_lock.hpp"
#include "../src/util.hpp"
#include "../src/sprite/system.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/renderer/font.hpp"
#include "../src/renderer/renderer.hpp"
#include "../src/renderer/types.hpp"
#include "../src/renderer/renderer_system.hpp"
#include "../src/renderer/transform.hpp"
#include "../src/media.hpp"
#include "../src/input/input_system.hpp"
#include "../src/input/key_state_tracker.hpp"
#include "../src/renderer/line_strip.hpp"
#include "../src/renderer/screenshot.hpp"
#include "../src/renderer/font_drawer_3d.hpp"
#include "../src/language.hpp"
#include "../src/endianness.hpp"
#include "../src/audio/audio_loader/audio_loader.hpp"
//#include "../src/audio/audio_player/audio_player.hpp"
//#include "../src/audio/audio_player/sound.hpp"
#include "../src/exception.hpp"
#include "../src/console/console_gfx.hpp"
#include "../src/console/console.hpp"
#include "../src/console/stdlib.hpp"
#include "../src/model/md3.hpp"
#include "../src/archive/archive_loader.hpp"
#include "../src/vector.hpp"
#include "../src/codecvt.hpp"
#include "../src/image/util.hpp"
#include "../src/multitree.hpp"
#include "../src/field.hpp"
#include "../src/language.hpp"
#include "../src/scoped_connection.hpp"
#include "../src/frames_counter.hpp"
#include "../src/fstream.hpp"
#include "../src/sstream.hpp"

//#include <hamigaki/archivers/zip_file.hpp>

namespace
{

/*sge::space_unit randf() { return double(std::rand())/RAND_MAX; }

sge::math::vector2 rand_point2() { return sge::math::vector2(randf(),randf()); }

sge::pos3 rand_point() { return sge::pos3(rand_point2(), 0); }*/

/*struct smallplayer
{
	sge::shared_ptr<sge::sound> sound;
	smallplayer(sge::shared_ptr<sge::sound> sound) : sound(sound) {}
	void operator()() { sound->play(false); }
};*/

struct console_activator
{
	sge::con::console_gfx &con;

	console_activator(sge::con::console_gfx &con) : con(con) {}

	void callback(const sge::key_pair &pair)
	{
		if (pair.key().code() == sge::kc::key_tab && pair.value())
			con.toggle();
	}
};
}

int main()
try
{
	std::wstring wstr(SGE_TEXT("/home/phil/local/lib/sge/libsgedevil.so"));
	std::string nstr(sge::narrow(wstr));
//	sge::multitree<int> test;
/*	typedef multi_tree<int> tree;
	tree t;
	tree::list l(t.children(t.begin()));
	l.push_back(10);
	tree::list l2(t.children(l.begin()));
	l2.push_back(20);
	tree::iterator it = t.begin();
	std::cout << *(++it) << '\n';*/

//	int a = 10;
//	sge::multitree<nondefctor> tree(nondefctor(a));
//	tree.push_back();
//	tree.push_back(nondefctor());

/*	int a = 10;
	nondefctor tmp;//(a);
	sge::multitree<nondefctor> tree(tmp);
	tree.push_back(nondefctor());
	tree.push_back(nondefctor());
*/
	std::srand(std::time(0));
	bool running = true;
	sge::plugin_manager pm;

//	const sge::plugin<sge::audio_player>::ptr_type audio_player_plugin = pm.get_plugin<sge::audio_player>().load();

//	sge::shared_ptr<sge::audio_player> audio_player(audio_player_plugin->get()());

/*	typedef std::vector< sge::plugin_manager::plugin_context<sge::audio_loader> > plugin_vector;
	plugin_vector audio_plugins;
	std::copy(pm.begin<sge::audio_loader>(),pm.end<sge::audio_loader>(),std::back_inserter(audio_plugins));

	typedef std::vector<sge::plugin_manager::plugin_context<sge::audio_loader>::ptr_type> loaded_plugins_vector;
	loaded_plugins_vector loaded;

	typedef std::vector< sge::shared_ptr<sge::audio_loader> > audio_loader_vector;
	audio_loader_vector loaders;*/

/*	sge::shared_ptr<sge::audio_file> soundfile;
	for (plugin_vector::iterator i = audio_plugins.begin(); i != audio_plugins.end(); ++i)
	{
		sge::plugin_manager::plugin_context<sge::audio_loader>::ptr_type np = i->load();
		loaded.push_back(np);
		sge::shared_ptr<sge::audio_loader> j(np->get()());
		loaders.push_back(j);
		const std::string path = sge::media_path()+"ding.wav";
		if (j->is_valid_file(path))
			soundfile = j->load(path);
	}
	if(!soundfile)
		throw std::runtime_error("ding.wav not found!");
	sge::shared_ptr<sge::sound> sound = audio_player->create_nonstream_sound(soundfile);*/

	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());
	const sge::renderer_caps_array caps(rs->caps());
	//for(sge::display_mode_array::size_type i = 0; i < caps.at(0).display_modes.size(); ++i)
//		std::cout << caps.at(0).display_modes[i] << '\n';
	//std::cout << caps.at(0).max_anisotropy_level << '\n';

	const sge::renderer_parameters param(sge::display_mode(1280,1024,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());

	const sge::plugin<sge::font_system>::ptr_type font_plugin = pm.get_plugin<sge::font_system>().load();
	const sge::font_system_ptr fs(font_plugin->get()());

	const sge::font_metrics_ptr metrics = fs->create_font(sge::media_path() / SGE_TEXT("fonts/default.ttf"), 15);
	const sge::font_drawer_ptr fn_drawer(new sge::font_drawer_3d(rend));

	sge::font_ptr fn(new sge::font(metrics,fn_drawer));

	sge::texture_manager texman(rend,sge::default_texture_creator<sge::no_fragmented_texture>(rend,sge::linear_filter));
	const sge::image_ptr console_image = pl->load_image(sge::media_path() / SGE_TEXT("black.jpg"));
	const sge::virtual_texture_ptr console_texture = sge::add_texture(texman,console_image);
	const sge::sprite_point pos(0,0);
	const sge::sprite_dim console_size(rend->screen_width(),rend->screen_height()/2);
	sge::con::console_gfx console(rend,console_texture,fn,is,pos,console_size);

	using boost::lambda::var;
	using boost::lambda::bind;
//	using boost::lambda::_1;
	using boost::lambda::if_;

	console_activator activator(console);

	const sge::scoped_connection cb(is->register_callback(if_(bind(&sge::key_type::code, bind(&sge::key_pair::key,boost::lambda::_1)) == sge::kc::key_escape)[var(running)=false]));
	const sge::scoped_connection cb2(is->register_callback(boost::bind(&console_activator::callback,&activator,_1)));

	sge::key_state_tracker ks(is);

	const sge::plugin<sge::archive_loader>::ptr_type archive_plugin(pm.get_plugin<sge::archive_loader>().load());
	const sge::archive_loader_ptr zip_archiver(archive_plugin->get()());

	const sge::archive_ptr kubal = zip_archiver->load_archive(sge::media_path() / SGE_TEXT("md3-kt_kubalwagon.pk3"));
	kubal->goto_begin();

	std::vector<unsigned char> uncompress_data;
	std::vector<unsigned char> image_data;
	//do
	{
		sge::archive_entry_ptr entry;
		kubal->open(entry);
	//	std::cout << entry->name() << ' ' << entry->uncompressed_size() << '\n';
		uncompress_data.resize(entry->uncompressed_size());
		entry->uncompress(sge::data(uncompress_data));
		entry.reset();

		kubal->next();
//		kubal->next();
		kubal->open(entry);
		image_data.resize(entry->uncompressed_size());
		entry->uncompress(sge::data(image_data));
	}
	//while(kubal->next());

	const sge::image_ptr tga = pl->load_image(sge::image_format::tga, reinterpret_cast<const sge::color*>(sge::data(image_data)), image_data.size());
	const sge::texture_ptr tex = sge::create_texture(rend, tga);

	rend->set_texture(tex);
	std::istream ifs(new boost::iostreams::stream_buffer<boost::iostreams::array_source>(boost::iostreams::array_source(reinterpret_cast<char*>(sge::data(uncompress_data)), uncompress_data.size())));

	std::noskipws(ifs);
	sge::md3_model model(ifs);

	const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::normal).add(sge::vertex_usage::tex), model.vertices());
	const sge::index_buffer_ptr model_ib = rend->create_index_buffer(model.indices());

	{
		const sge::scoped_lock<sge::vertex_buffer_ptr> _lock(model_vb);
		model.fill_vertices(model_vb);
	}

	{
		const sge::scoped_lock<sge::index_buffer_ptr> _lock(model_ib);
		model.fill_indices(model_ib);
	}

	rend->set_bool_state(sge::bool_state::enable_lighting, true);
	rend->set_bool_state(sge::bool_state::enable_zbuffer, true);
	rend->set_bool_state(sge::bool_state::enable_culling, true);
	rend->set_bool_state(sge::bool_state::clear_zbuffer, true);
	rend->set_bool_state(sge::bool_state::clear_backbuffer, true);
	rend->set_cull_mode(sge::cull_mode::front);
	rend->set_float_state(sge::float_state::zbuffer_clear_val, 0);
	rend->set_depth_func(sge::depth_func::greater);

	rend->set_light(0, sge::light(sge::color4(1, 0.5, 0, 0), sge::color4(1, 0.5, 0, 0), sge::color4(1, 0, 0, 0), sge::light::position_type(0, 0, 0), sge::light::direction_type(0, 0, -1), 0.2, 0, 0, 1, 90));
	rend->enable_light(0, true);

	sge::math::vector3 translation(0, 0, -200);
	sge::space_unit angle(0);
	sge::frames_counter frames;
	sge::timer rotate_timer(5000);
	sge::timer move_timer(5);

//	rend->set_draw_mode(sge::draw_mode::line);

	//const sge::string some_text(SGE_TEXT("abc\n\nasadgasdgsadg ahsfh ashsdg sadgfas d asd\n asdgg asdg asdg asg asdg sa\nb"));
	const sge::string some_text(L"abc\n\nasadgasdgsadg ahsfh ashsdg sadgfas d asd\n asdgg asdg asdg asg asdg sa\nb");
	while(running)
	{
	//	if (sound->status() != sge::sound::status_stopped)
	//		sound->update();

		frames.update();
		rotate_timer.update();
		move_timer.update();
		
		translation.x() -= ks[sge::kc::key_left] * move_timer.elapsed_frames();
		translation.x() += ks[sge::kc::key_right] * move_timer.elapsed_frames();
		translation.z() -= ks[sge::kc::key_up] * move_timer.elapsed_frames();
		translation.z() += ks[sge::kc::key_down] * move_timer.elapsed_frames();
//		if(ks[sge::kc::key_return])
//			sge::screenshot(rend,pl,"shot.png");

		rend->begin_rendering();
		rend->transform(sge::math::matrix_rotation_x(angle) * sge::math::matrix_translation(translation));
//		angle = rotate_timer.elapsed_frames() * sge::math::PI*2;
		rend->projection(sge::math::matrix_perspective(static_cast<sge::space_unit>(rend->screen_width())/rend->screen_height(), 45, 1, 10));
		rend->render(model_vb, model_ib, 0, model_vb->size(), sge::indexed_primitive_type::triangle, model.indices() / 3, 0);

		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();
		//ss.transform(sge::math::matrix_translation(translation));
		//ss.render();
		//man.process();
		fn->draw_text(some_text, sge::font_pos(100,100), sge::font_dim(20,500), sge::font_align_h::right, sge::font_align_v::bottom);
		//ls.render();


		//rend->set_bool_state(sge::bool_state::enable_culling,false);
		if (console.active())
			console.draw();
		rend->end_rendering();
	}
	return EXIT_SUCCESS;
}
/*catch(const sge::exception& e)
{
	std::wcerr << "Program terminated (sge::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}*/
catch(const std::exception& e)
{
	std::wcerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
/*catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}*/

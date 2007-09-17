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
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include "../src/iconv.hpp"
#include "../src/math/constants.hpp"
#include "../src/plugin_manager.hpp"
#include "../src/renderer/lock_ptr.hpp"
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
#include "../src/audio/audio_player/audio_player.hpp"
#include "../src/audio/audio_player/sound.hpp"
#include "../src/exception.hpp"
#include "../src/console/console_gfx.hpp"
#include "../src/console/console.hpp"
#include "../src/model/md3.hpp"
#include "../src/archive/archive_loader.hpp"
#include "../src/vector.hpp"
#include "../src/codecvt.hpp"
#include "../src/image/util.hpp"
#include "../src/multitree.hpp"

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
		if (pair.key().code() == sge::kc::key_tab && !pair.zero())
			con.active(!con.active());
	}
};
}

/*using sge::space_unit;
sge::math::space_matrix frustum_matrix(const space_unit left, const space_unit right, const space_unit bottom, const space_unit top, const space_unit near, const space_unit far)
{
	return sge::math::space_matrix(
		2*near/(right-left),0,(right+left)/(right-left),0,
		0,2*near/(top-bottom),(top+bottom)/(top-bottom),0,
		0,0,(far+near)/(far-near),2*far*near/(far-near),
		0,0,-1,0
	);
}*/

/*inline sge::math::space_matrix matrix_perspective(const space_unit aspect, const space_unit fov, const space_unit near, const space_unit far)
{
	const space_unit h = space_unit(1) / std::tan(fov / space_unit(2)),
	                 w = h / aspect,
	                 q = (far + near) / (far - near);
	return sge::math::space_matrix
	       (w, 0,       0, 0,
	        0, h,       0, 0,
	        0, 0,       q, 1,
	        0, 0, (2*far*near)/(near-far), 0);
}*/
struct nondefctor
{
  int *a;

  nondefctor() : a(0) {}
  nondefctor(int &a) : a(&a) {}
};


int main()
//try
{
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

	const std::string s = "blubbbbbäüöß";
	const std::wstring ws = sge::iconv(s);
//	std::wcout << ws << L'\n';
//	const std::wstring ws = L"äöüßblublblbu";
//	const std::string s = sge::iconv(ws);
//	std::wcout << ws << " ws: " << ws.size() << ", s: " << s.size() << '\n';
	//std::wcout << L"äöüß\n";

	const sge::plugin<sge::audio_player>::ptr_type audio_player_plugin = pm.get_plugin<sge::audio_player>().load();

	sge::shared_ptr<sge::audio_player> audio_player(audio_player_plugin->get()());

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

	const sge::font_metrics_ptr metrics = fs->create_font(sge::media_path() + "fonts/default.ttf", 14);
	const sge::font_drawer_ptr fn_drawer(new sge::font_drawer_3d(rend));

	sge::font fn(metrics, fn_drawer);

	sge::image_ptr im = pl->load_image(sge::media_path() + "black.jpg");
	sge::texture_ptr con_tex = rend->create_texture(im->data(),im->width(),im->height(),sge::linear_filter);
	sge::con::console_gfx console(rend,is,fn,sge::colors::white,con_tex);

/*	sge::font fn(rend, fs, sge::media_path() + "fonts/default.ttf", 32);
	sge::sprite_system ss(rend, 0, 2);
	sge::image_ptr im = pl->load_image(sge::media_path() + "mainskin/cancel_0.png");
	sge::image_ptr im2 = pl->load_image(sge::media_path() + "mainskin/button.png");
	sge::image_ptr im3 = pl->load_image(sge::media_path() + "mainskin/clickbox_quad_pressed.png");
	const std::string tex[] = { "bender", "tex2", "tex3" };

	sge::texture_map_ptr tex_map = ss.get_texture_map();
	tex_map->add_texture(im,tex[0]);
	tex_map->add_texture(im2,tex[1]);
	tex_map->add_texture(im3,tex[2]);*/
//	boost::ptr_vector<sge::sprite> sprites;
//	for(unsigned i = 0; i < 4; ++i)
//		sprites.push_back(new sge::sprite(ss,sge::point(0,i*0.3),sge::dim(0.3,0.3),0,tex[i % 3]));
//	sprites.back().set_color(sge::colors::red);

/*	std::vector<sge::sprite> sprites;
	for(unsigned i = 0; i < 100; ++i)
		sprites.push_back(sge::sprite(ss,rand_point2(),sge::math::dim2(0.3,0.3),tex[i % 3], sge::colors::white));

	for(unsigned i = 0; i < 100; ++i)
		sprites[i] = sge::sprite(ss,rand_point2(),sge::math::dim2(0.3,0.3),tex[i % 3], sge::colors::white);*/


//	sge::sprite spr(ss, sge::math::vector2(0.25,0.25), sge::math::dim2(0.5,0.5), /*tex[0]*/sge::texture_map::no_texture, sge::colors::yellow);
//	spr.set_texture(tex[1],1);
/*	sge::sprite spr2(ss, sge::math::vector2(0.25,-0.25), sge::math::dim2(0.25,3), tex[1], sge::colors::red);
	spr2.set_texture(tex[2],1);

	sge::gui::manager man(rend, is, fn, pl, sge::media_path() + "mainskin/", 0.05);
	sge::gui::frame fr1(man,0,sge::gui::point(0,0), sge::gui::dim(1,1), "cancel_0");
	sge::gui::button btn1(man, &fr1, sge::iconv("Quit!"), sge::gui::point(0,0.1), sge::gui::dim(0.45,0.1));
	sge::gui::button btn2(man, &fr1, sge::iconv("Play!"), sge::gui::point(0,0.3), sge::gui::dim(0.45,0.1));
	sge::gui::list list1(man, &fr1, sge::gui::point(0.5,0.1), sge::gui::dim(0.2,0.8));
	sge::gui::icon_button icbtn1(man, &fr1,sge::gui::point(0,0.8), sge::gui::dim(0.5,0.1), "newgame_0", "newgame_1", "newgame_2");
	sge::gui::text_edit te1(man, &fr1, sge::gui::point(0,0.5), sge::gui::dim(0.7,0.3), sge::iconv("abc"));
	list1.push_back(sge::iconv("LOL"));
	list1.push_back(sge::iconv("BAR"));
	list1.push_back(sge::iconv("ROFL!"));

	for(unsigned i = 0; i < 20; ++i)
		list1.push_back(sge::iconv("jgAB" + boost::lexical_cast<std::string>(i)));

	sge::gui::static_text st(man, &fr1, sge::iconv("hellothere,i'mamultiline dstatic_text"), sge::gui::point(0.5,0.8), sge::gui::dim(0.3,0.1), sge::colors::red);*/

	using boost::lambda::var;
	using boost::lambda::bind;
//	using boost::lambda::_1;
	using boost::lambda::if_;

	console_activator activator(console);

	boost::signals::scoped_connection cb(is->register_callback(if_(bind(&sge::key_type::code, bind(&sge::key_pair::key,boost::lambda::_1)) == sge::kc::key_escape)[var(running)=false]));
	boost::signals::scoped_connection cb2(is->register_callback(boost::bind(&console_activator::callback,&activator,_1)));
//	boost::signals::scoped_connection cb2(btn1.click_signal.connect(var(running) = false));
//	boost::signals::scoped_connection cb3(btn2.click_signal.connect(smallplayer(sound)));

	sge::timer timer(30);
	sge::timer frames(1000);

	unsigned fps = 0, cur_fps = 0;
//	sge::space_unit angle = 0;

	sge::key_state_tracker ks(is);

/*	sge::line_strip ls(rend, sge::colors::red);
	for(int i = 0; i < 5; ++i)
		ls.add(rand_point());
	ls.loop(true);*/

	//const sge::string some_text(sge::iconv("abcdefgh\ni\n\njklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789\ntesttest"));

//	sge::con::console_gfx con(rend, is, fn, sge::image_loader_handler(sge::media_path(), pl));

	const sge::plugin<sge::archive_loader>::ptr_type archive_plugin(pm.get_plugin<sge::archive_loader>().load());
	const sge::archive_loader_ptr zip_archiver(archive_plugin->get()());

	const sge::archive_ptr kubal = zip_archiver->load_archive(sge::media_path() + "md3-kt_kubalwagon.pk3");
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
		kubal->next();
		kubal->open(entry);
		image_data.resize(entry->uncompressed_size());
		entry->uncompress(sge::data(image_data));
	}
	//while(kubal->next());

	//const sge::image_ptr tga = pl->load_image(sge::media_path() + "euro_frnt_2.tga");
	const sge::image_ptr tga = pl->load_image(sge::image_format::tga, reinterpret_cast<const sge::color*>(sge::data(image_data)), image_data.size());
	const sge::texture_ptr tex = sge::create_texture(rend, tga);

	rend->set_texture(tex);
	//std::istream ifs(new sge::memory_buf(reinterpret_cast<char*>(sge::data(uncompress_data)), uncompress_data.size()));
	std::istream ifs(new boost::iostreams::stream_buffer<boost::iostreams::array_source>(boost::iostreams::array_source(reinterpret_cast<char*>(sge::data(uncompress_data)), uncompress_data.size())));

	/*hamigaki::archivers::zip_file_source archive(sge::media_path() + "md3-kt_kubalwagon.pk3");
	archive.next_entry();
	std::vector<char> uncompress_data(30000);
	std::streamsize already_read = 0;
	while(const std::streamsize sz = archive.read(sge::data(uncompress_data) + already_read, uncompress_data.size() - already_read))
	{
		if(sz == -1)
			break;

		already_read += sz;
		if(already_read == uncompress_data.size())
			uncompress_data.resize(uncompress_data.size()*2);
	}*/
	//std::istream ifs(new sge::memory_buf(sge::data(uncompress_data), already_read));
	std::noskipws(ifs);
//	ifs.exceptions(std::ios_base::failbit | std::ios_base::badbit | std::ios_base::eofbit);
/*	std::ifstream ifs((sge::media_path() + "european_fnt_v2.md3").c_str(), std::ios_base::binary);
	if(!ifs.is_open())
	{
		std::cerr << "Can't load the model.\n";
		return EXIT_FAILURE;
	}*/
	sge::md3_model model(ifs);

	sge::vertex_buffer::size_type vb_sz = 0;
	for(sge::md3_model::surface_vector::const_iterator surf_it = model.surfaces.begin(); surf_it != model.surfaces.end(); ++surf_it)
		vb_sz += surf_it->transformed_vertices.size();
	const sge::vertex_buffer_ptr model_vb = rend->create_vertex_buffer(sge::vertex_format().add(sge::vertex_usage::pos).add(sge::vertex_usage::tex), vb_sz);


	sge::index_buffer::size_type ib_sz = 0;
	for(sge::md3_model::surface_vector::const_iterator surf_it = model.surfaces.begin(); surf_it != model.surfaces.end(); ++surf_it)
		ib_sz += surf_it->triangles.size();
	const sge::index_buffer_ptr model_ib = rend->create_index_buffer(ib_sz * 3);

	std::vector<sge::index_buffer::size_type> offsets;
	offsets.push_back(0);
	{
		sge::lock_ptr<sge::vertex_buffer_ptr> _lock(model_vb);
		sge::vertex_buffer::iterator vbit = model_vb->begin();
		for(sge::md3_model::surface_vector::const_iterator surf_it = model.surfaces.begin(); surf_it != model.surfaces.end(); ++surf_it)
		{
			const sge::md3_model::surface& surf = *surf_it;

			const sge::vertex_buffer::iterator vbold = vbit;
			for(sge::md3_model::surface::transformed_vertex_vector::size_type sz = 0; sz < surf.transformed_vertices.size(); ++sz)
			{
				(vbit  )->pos() = surf.transformed_vertices.at(sz).pos;
				(vbit++)->tex() = surf.st.at(sz).tex;
			}	
			offsets.push_back(offsets.back() + surf.transformed_vertices.size());
		}

	}

	{
		sge::lock_ptr<sge::index_buffer_ptr> _lock(model_ib);
		sge::index_buffer::iterator ibit = model_ib->begin();
		for(sge::md3_model::surface_vector::const_iterator surf_it = model.surfaces.begin(); surf_it != model.surfaces.end(); ++surf_it)
		{
			const sge::md3_model::surface& surf = *surf_it;
			for(sge::md3_model::surface::triangle_vector::const_iterator it = surf.triangles.begin(); it != surf.triangles.end(); ++it)
			{
				const sge::index_buffer::value_type offset = offsets[surf_it - model.surfaces.begin()];
				*ibit++ = it->indices[0] + offset;
				*ibit++ = it->indices[1] + offset;
				*ibit++ = it->indices[2] + offset;
			}
		}
	}

	rend->set_bool_state(sge::bool_state::enable_lighting, true);
	rend->set_bool_state(sge::bool_state::enable_zbuffer, true);
	rend->set_bool_state(sge::bool_state::enable_culling, true);
	rend->set_bool_state(sge::bool_state::clear_zbuffer, true);
	rend->set_bool_state(sge::bool_state::clear_backbuffer, true);
	rend->set_cull_mode(sge::cull_mode::front);
	rend->set_float_state(sge::float_state::zbuffer_clear_val, 0);
	rend->set_depth_func(sge::depth_func::greater);

	rend->set_light(0, sge::light(sge::color4(1, 0.5, 0, 0), sge::color4(1, 0.5, 0, 0), sge::color4(1, 0, 0, 0), sge::light::position_type(0, 0, 0), sge::light::direction_type(0, 0, -1), 0.5, 0, 0, 1, 90));
	rend->enable_light(0, true);

	sge::math::vector3 translation(0, 0, -200);
	float angle(0);
	sge::timer frame_timer(1000);

	const sge::string some_text(sge::iconv("abc\n\nasadgasdgsadg ahsfh ashsdg sadgfas d asd\n asdgg asdg asdg asg asdg sa\nb"));
	while(running)
	{
	//	if (sound->status() != sge::sound::status_stopped)
	//		sound->update();

		if(frames.update() > 0)
		{
			cur_fps = fps;
			fps = 0;
		}
		translation.x() -= ks[sge::kc::key_left] * 0.001;
		translation.x() += ks[sge::kc::key_right] * 0.001;
		translation.z() -= ks[sge::kc::key_up] * 0.3;
		translation.z() += ks[sge::kc::key_down] * 0.3;
//		if(ks[sge::kc::key_return])
//			sge::screenshot(rend,pl,"shot.png");
		if(timer.update() > 0)
			angle += sge::math::PI*0.01;

		rend->begin_rendering();
		rend->transform(sge::math::matrix_rotation_x(angle) * sge::math::matrix_translation(translation));
		angle = frame_timer.elapsed_frames() * sge::math::PI*2 * 0.1;
		rend->projection(sge::math::matrix_perspective(static_cast<sge::space_unit>(rend->screen_width())/rend->screen_height(), 90, 1, 10));
		rend->render(model_vb, model_ib, 0, model_vb->size(), sge::indexed_primitive_type::triangle, ib_sz, 0);

		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();
		//ss.transform(sge::math::matrix_translation(translation));
		//ss.render();
		//man.process();
		//fn.draw_text(some_text, sge::font_pos(100,100), sge::font_dim(20,500), sge::font_align_h::right, sge::font_align_v::bottom);
//		fn.draw_text(sge::iconv(boost::lexical_cast<std::string>(cur_fps)),sge::font_pos(100,400),sge::font_dim(500,1000), sge::font_flags::align_left | sge::font_flags::align_top);
		//ls.render();


		//rend->set_bool_state(sge::bool_state::enable_culling,false);
		//if (console.active())
		//	console.draw();
		rend->end_rendering();
		++fps;
	}
	return EXIT_SUCCESS;
}
/*catch(const std::exception& e)
{
	std::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}*/

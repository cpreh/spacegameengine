/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../src/math/constants.hpp"
#include "../src/plugin_manager.hpp"
#include "../src/renderer/lock_ptr.hpp"
#include "../src/util.hpp"
#include "../src/sprite/system.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/renderer/font.hpp"
#include "../src/renderer/renderer.hpp"
#include "../src/renderer/types.hpp"
#include "../src/media.hpp"
#include "../src/gui/manager.hpp"
#include "../src/gui/button.hpp"
#include "../src/gui/text_edit.hpp"
#include "../src/gui/list.hpp"
#include "../src/gui/icon_button.hpp"
#include "../src/gui/frame.hpp"
#include "../src/gui/static_text.hpp"
#include "../src/input/input_system.hpp"
#include "../src/input/key_state_tracker.hpp"
#include "../src/renderer/line_strip.hpp"
#include "../src/renderer/screenshot.hpp"
#include "../src/language.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <sstream>
#include <iostream>

sge::pos3 rand_point() { return sge::pos3(double(std::rand())/RAND_MAX,double(std::rand())/(RAND_MAX), 0); }

sge::point rand_point2() { return sge::point(double(std::rand())/RAND_MAX,double(std::rand())/(RAND_MAX)); }

int main()
try
{
	std::srand(std::time(0));
	bool running = true;
	sge::plugin_manager pm;
	sge::renderer_system_ptr rs = pm.get_plugin<sge::renderer_system>();

	/*sge::renderer_caps_array caps;
	rs->caps(caps);

	for(sge::display_mode_array::size_type i = 0; i < caps.at(0).display_modes.size(); ++i)
	{
		const sge::display_mode& mode = caps.at(0).display_modes[i];
		std::cerr << mode.width << ' ' << mode.height << ' ' << sge::bit_depth_bit_count(mode.depth) << ' ' << mode.refresh_rate << '\n';
	}*/

	const sge::renderer_parameters param(sge::display_mode(1024,768,sge::BD_32,100), false);
	sge::renderer_ptr rend = rs->create_renderer(param);
	sge::image_loader_ptr pl = pm.get_plugin<sge::image_loader>();
	sge::font_system_ptr fs = pm.get_plugin<sge::font_system>();
	sge::input_system_ptr is = pm.get_plugin<sge::input_system>(rend->get_window());
	sge::font fn(rend,fs,"/usr/share/fonts/corefonts/arialbd.ttf",32);
	sge::sprite_system ss(rend, 0, 2);
	sge::image_ptr im = pl->load_image(sge::media_path() + "/mainskin/cancel_0.png");
	sge::image_ptr im2 = pl->load_image(sge::media_path() + "/mainskin/button.png");
	sge::image_ptr im3 = pl->load_image(sge::media_path() + "/mainskin/clickbox_quad_pressed.png");

	const std::string tex[] = { "bender", "tex2", "tex3" };

	sge::texture_map_ptr tex_map = ss.get_texture_map();
	tex_map->add_texture(im,tex[0]);
	tex_map->add_texture(im2,tex[1]);
	tex_map->add_texture(im3,tex[2]);

//	boost::ptr_vector<sge::sprite> sprites;
//	for(unsigned i = 0; i < 4; ++i)
//		sprites.push_back(new sge::sprite(ss,sge::point(0,i*0.3),sge::dim(0.3,0.3),0,tex[i % 3]));
//	sprites.back().set_color(sge::colors::red);
	
	std::vector<sge::sprite> sprites;
	for(unsigned i = 0; i < 100; ++i)
		sprites.push_back(sge::sprite(ss,rand_point2(),sge::dim(0.3,0.3),tex[i % 3], sge::colors::white));

	for(unsigned i = 0; i < 100; ++i)
		sprites[i] = sge::sprite(ss,rand_point2(),sge::dim(0.3,0.3),tex[i % 3], sge::colors::white);


	sge::sprite spr(ss, sge::point(0.25,0.25), sge::dim(0.5,0.5), /*tex[0]*/sge::texture_map::no_texture, sge::colors::yellow);
//	spr.set_texture(tex[1],1);
	sge::sprite spr2(ss, sge::point(0.25,-0.25), sge::dim(0.25,3), tex[1], sge::colors::red);
	spr2.set_texture(tex[2],1);

	sge::gui::manager man(rend, is, fn, pl, sge::media_path() + "/mainskin/", 0.05);
	sge::gui::frame fr1(man,0,sge::point(0,0),sge::dim(1,1),"cancel_0");
	sge::gui::button btn1(man,&fr1,"Beenden!",sge::point(0,0.1),sge::dim(0.45,0.1));
	sge::gui::list list1(man,&fr1,sge::point(0.5,0.1),sge::dim(0.2,0.8));
	sge::gui::icon_button icbtn1(man,&fr1,sge::point(0,0.8),sge::dim(0.5,0.1),"newgame_0","newgame_1","newgame_2");
	sge::gui::text_edit te1(man,&fr1,sge::point(0,0.5),sge::dim(0.7,0.3),"abc");
	list1.push_back("LOL");
	list1.push_back("BAR");
	list1.push_back("ROFL!");

	for(int i = 0; i < 20; ++i)
	{
		std::ostringstream os;
		os << "jgAB" << i;
		list1.push_back(os.str());
	}

	sge::gui::static_text st(man, &fr1, "hellothere,i'mamultiline dstatic_text", sge::point(0.5,0.8), sge::dim(0.3,0.1), sge::colors::red);
	
	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::_1;
	using boost::lambda::if_;
	
	boost::signals::scoped_connection cb(is->register_callback(if_(bind(&sge::key_type::code, bind(&sge::key_pair::first,_1)) == sge::KC_ESC)[var(running)=false]));
	boost::signals::scoped_connection cb2(btn1.click_signal.connect(var(running) = false));

	sge::timer timer(30);
	sge::timer frames(1000);

	unsigned fps = 0, cur_fps = 0;
	sge::space_unit angle = 0;

	sge::key_state_tracker ks(is);

	sge::vector3 translation;

	sge::line_strip ls(rend, sge::colors::red);
	for(int i = 0; i < 5; ++i)
		ls.add(rand_point());

	const std::string some_text("abcdefgh\ni\njklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789\ntesttest");

	while(running)
	{
		if(frames.update())
		{
			cur_fps = fps;
			fps = 0;
		}
		if(ks[sge::KC_LEFT])
			translation.x() -= 0.001;
		if(ks[sge::KC_RIGHT])
			translation.x() += 0.001;
		if(ks[sge::KC_UP])
			translation.y() -= 0.001;
		if(ks[sge::KC_DOWN])
			translation.y() += 0.001;
		if(ks[sge::KC_RETURN])
			sge::screenshot(rend,pl,"./shot.png");
		if(timer.update())
			angle += sge::PI*0.01;

		spr.rotate(angle);

		rend->begin_rendering();
		is->dispatch();
		ss.transform(sge::math::matrix_translation(translation));
		ss.render();
		man.process();
//		fn.transform(sge::math::matrix_rotation_x(angle));
//		fn.projection(sge::math::transpose(sge::math::matrix_perspective(sge::space_unit(rend->screen_height())/rend->screen_width(),sge::PI,0,1)));
//		fn.internal_transformation(sge::math::matrix_identity());
		fn.height_pixel_scale(1);
		fn.height(0.05);
		fn.draw_text(some_text,sge::point(0.2,0.2),sge::dim(0.8,0.8),sge::colors::green/*, sge::FTF_NoLineWrap*/);
		std::ostringstream os;
		os << cur_fps;
		fn.transform(sge::math::matrix_identity());
		fn.draw_text(os.str(),sge::point(0.1,0),sge::dim(1,1),sge::colors::purple);
		ls.draw(true);
		rend->end_rendering();
		++fps;
	}
}
catch(const std::exception& e)
{
	std::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return -1;
}
catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return -1;
}

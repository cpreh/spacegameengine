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
#include <iomanip>

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>

#include "../src/init.hpp"
#include "../src/input/key_state_tracker.hpp"
#include "../src/math/constants.hpp"
#include "../src/renderer/scoped_lock.hpp"
#include "../src/renderer/screenshot.hpp"
#include "../src/sprite/sprite.hpp"
#include "../src/sprite/system.hpp"
#include "../src/texture/no_fragmented_texture.hpp"

#include "../src/gui/color.hpp"
#include "../src/gui/manager.hpp"
#include "../src/gui/button.hpp"
#include "../src/gui/inputprocessor.hpp"

inline sge::pos3 at_pixel(int x, int y) {
	return sge::pos3(
		(x-400) / 400.0,
		-(y-300) / 300.0,
		0
	);
}

sge::gui::canvas canvas;
bool changed;

sge::color colors[] = {
	sge::colors::black,
	sge::colors::coral,
	sge::colors::gold,
	sge::colors::skyblue,
	sge::colors::limegreen,
	sge::colors::papayawhip
};

struct myIA : public sge::gui::inputacceptor {
	using sge::gui::inputacceptor::inputprocessor_attach;
	using sge::gui::inputacceptor::inputprocessor_detach;

	sge::vertex_buffer_ptr cuvb;
	int color;
	myIA(sge::vertex_buffer_ptr cuvb) : cuvb(cuvb), color(0) {}

	sge::gui::point inputprocessor_offset() const { return sge::gui::point(0,0); }

	void dump(const sge::gui::events::mouse_event &me, std::string extra = "") const {
		std::cout
			<< "Mouse at "
			<< std::setw(4) << me.global_position.x << std::setw(0)
			<< ","
			<< std::setw(4) << me.global_position.y << std::setw(0)
			<< " ("
			<< ((me.pressstate.find(sge::gui::events::mouse_event::LEFT  ) != me.pressstate.end()) ? "L" : "_")
			<< " "
			<< ((me.pressstate.find(sge::gui::events::mouse_event::MIDDLE) != me.pressstate.end()) ? "M" : "_")
			<< " "
			<< ((me.pressstate.find(sge::gui::events::mouse_event::RIGHT ) != me.pressstate.end()) ? "R" : "_")
			<< ") "
			<< extra
			<< std::endl;
	}

	void paint(const sge::gui::events::mouse_event &me) {
		canvas.pixel(me.global_position) = colors[color];
		changed = true;
	}

	static std::string pressed_button(const sge::gui::events::mouse_event &me) {
		switch(me.pressed) {
			case sge::gui::events::mouse_event::NONE:
				return "NONE";
			case sge::gui::events::mouse_event::LEFT:
				return "LEFT";
			case sge::gui::events::mouse_event::RIGHT:
				return "RGHT";
			case sge::gui::events::mouse_event::MIDDLE:
				return "MDDL";
			default:
				return "UNKN";
		}
	}

	sge::gui::inputprocessor::response inject_mouse_move    (const sge::gui::events::mouse_event &me) {
		{
			sge::scoped_lock<sge::vertex_buffer_ptr> _lock(cuvb);
			sge::vertex_buffer::iterator it = cuvb->begin();
			it->pos() = at_pixel(me.global_position.x +  0, me.global_position.y +  0); ++it;
			it->pos() = at_pixel(me.global_position.x + 16, me.global_position.y + 32); ++it;
			it->pos() = at_pixel(me.global_position.x + 32, me.global_position.y + 16);
		}
		if (me.is_pressed(sge::gui::events::mouse_event::LEFT))
			paint(me);
		dump(me);
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_down    (const sge::gui::events::mouse_event &me) {
		dump(me, "press"  );
		if (me.pressed == sge::gui::events::mouse_event::LEFT)
			paint(me);
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_up      (const sge::gui::events::mouse_event &me) {
		dump(me, "release");
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_wheel   (const sge::gui::events::mouse_wheel_event &me) { dump(me, (me.direction == sge::gui::events::mouse_wheel_event::UP) ? "UP" : "DOWN"); return sge::gui::inputprocessor::response_continue; }
	sge::gui::inputprocessor::response inject_mouse_click   (const sge::gui::events::mouse_event &me) {
		dump(me, pressed_button(me)+" CLICK");
		if (me.pressed == sge::gui::events::mouse_event::RIGHT) {
			sge::scoped_lock<sge::vertex_buffer_ptr> _lock(cuvb);
			cuvb->begin()->diffuse() = colors[color = (color+1) % 6];
		}
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_dblclick(const sge::gui::events::mouse_event &me) { dump(me, pressed_button(me)+" DOUBLE CLICK"); return sge::gui::inputprocessor::response_continue; }
};

int main()
try
{
	std::srand(std::time(0));
	bool running = true;

	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(800, 600);
	sys.init<sge::init::input>();
	sys.init<sge::init::image_loader>();

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	sge::input_system_ptr is   = sys.input_system;
	sge::renderer_ptr     rend = sys.renderer;
	sge::image_loader_ptr pl   = sys.image_loader;

	boost::signals::scoped_connection escape_handler(sys.input_system->register_callback(
		if_(bind(&sge::key_type::code, bind(&sge::key_pair::key, boost::lambda::_1)) == sge::kc::key_escape)
			[var(running)=false])
	);

	sge::vertex_buffer_ptr bgvb, cuvb, fgvb;
	sge::index_buffer_ptr  bgib, cuib, fgib;

	sge::fragmented_texture_ptr mytex(new sge::no_fragmented_texture(rend, sge::point_filter));
	sge::texture_manager texmgr(rend, mytex);

	canvas.resize(sge::gui::dim2(800, 600));
	canvas.fill(sge::colors::transparent);
	sge::virtual_texture_ptr canvastex = canvas.to_texture(texmgr);

	{
		const sge::index_buffer::value_type indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		fgib = bgib = rend->create_index_buffer(6, sge::resource_flags::default_, indices);
		cuib = rend->create_index_buffer(3, sge::resource_flags::default_, indices);
	}

	bgvb =
		rend->create_vertex_buffer(
		sge::vertex_format().add(sge::vertex_usage::pos)
		                    .add(sge::vertex_usage::diffuse),
		4);
	{
		sge::scoped_lock<sge::vertex_buffer_ptr> _lock(bgvb);
		sge::vertex_buffer::iterator it = bgvb->begin();

		it->pos() = sge::pos3(-1,  1, 0); it->diffuse() = sge::colors::blue  ; ++it; // top left
		it->pos() = sge::pos3( 1,  1, 0); it->diffuse() = sge::colors::yellow; ++it; // top right
		it->pos() = sge::pos3(-1, -1, 0); it->diffuse() = sge::colors::red   ; ++it; // bottom left
		it->pos() = sge::pos3( 1, -1, 0); it->diffuse() = sge::colors::green ;       // bottom right
	}

	cuvb =
		rend->create_vertex_buffer(
		sge::vertex_format().add(sge::vertex_usage::pos)
		                    .add(sge::vertex_usage::diffuse),
		3);
	{
		sge::scoped_lock<sge::vertex_buffer_ptr> _lock(cuvb);
		sge::vertex_buffer::iterator it = cuvb->begin();
		it->diffuse() = colors[0]; ++it;
		it->diffuse() = sge::colors::white; ++it;
		it->diffuse() = sge::colors::white;
	}

	fgvb =
		rend->create_vertex_buffer(
		sge::vertex_format().add(sge::vertex_usage::pos)
		                    .add(sge::vertex_usage::tex),
		4);
	{
		sge::scoped_lock<sge::vertex_buffer_ptr> _lock(fgvb);
		sge::vertex_buffer::iterator it = fgvb->begin();

		it->pos() = sge::pos3(-1,  1, 0); it->tex() = canvastex->translate(0, 0); ++it; // top left
		it->pos() = sge::pos3( 1,  1, 0); it->tex() = canvastex->translate(1, 0); ++it; // top right
		it->pos() = sge::pos3(-1, -1, 0); it->tex() = canvastex->translate(0, 1); ++it; // bottom left
		it->pos() = sge::pos3( 1, -1, 0); it->tex() = canvastex->translate(1, 1); ++it; // bottom right
	}


	sge::key_state_tracker ks(is);
	sge::gui::inputprocessor ip(is);
	std::cout << "created ip" << std::endl;
	myIA ia(cuvb);
	std::cout << "created ia" << std::endl;
	ia.inputprocessor_attach(ip);
	std::cout << "attached ia" << std::endl;

	ip.option(sge::gui::inputprocessor::double_click_duration, 0); // disable double click

	rend->set_bool_state(sge::bool_state::enable_alpha_blending, true);

	while(running)
	{
		if(ks[sge::kc::key_return])
			sge::screenshot(rend,pl,"shot.png");

		rend->begin_rendering();
		rend->get_window()->dispatch();
		sge::window::dispatch();
		is->dispatch();
		ip.dispatch();

		rend->render(bgvb, bgib, 0, bgvb->size(), sge::indexed_primitive_type::triangle, 2, 0);

		if (changed) {
			canvastex = canvas.to_texture(texmgr, canvastex);
			changed = false;
		}

		rend->set_texture(canvastex->my_texture());
		rend->render(fgvb, fgib, 0, fgvb->size(), sge::indexed_primitive_type::triangle, 2, 0);

		rend->set_texture(sge::texture_base_ptr());
		rend->render(cuvb, cuib, 0, cuvb->size(), sge::indexed_primitive_type::triangle, 1, 0);

		rend->end_rendering();
	}
	return EXIT_SUCCESS;
}
catch(const std::exception& e)
{
	std::cerr << "Program terminated (std::exception caught): " << e.what() << '\n';
	return EXIT_FAILURE;
}
catch(...)
{
	std::cerr << "Program terminated (unknown exception caught)!\n";
	return EXIT_FAILURE;
}

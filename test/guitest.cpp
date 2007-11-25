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

#include "../src/input/input_system.hpp"
#include "../src/input/key_state_tracker.hpp"
#include "../src/math/constants.hpp"
#include "../src/renderer/scoped_lock.hpp"
#include "../src/renderer/renderer_system.hpp"
#include "../src/renderer/screenshot.hpp"
#include "../src/plugin_manager.hpp"
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

struct myIA : public sge::gui::inputacceptor {
	using sge::gui::inputacceptor::inputprocessor_attach;
	using sge::gui::inputacceptor::inputprocessor_detach;

	sge::vertex_buffer_ptr cuvb;
	myIA(sge::vertex_buffer_ptr cuvb) : cuvb(cuvb) {}

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
		dump(me);
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_down    (const sge::gui::events::mouse_event &me) {
		dump(me, "press"  );
		{
			sge::scoped_lock<sge::vertex_buffer_ptr> _lock(cuvb);
			sge::vertex_buffer::iterator it = cuvb->begin();
			switch (me.pressed) {
				case sge::gui::events::mouse_event::LEFT:
					(  ++it)->diffuse() = sge::static_color<160,160,255>::value; break;
				case sge::gui::events::mouse_event::RIGHT:
					(++++it)->diffuse() = sge::static_color<255,160,160>::value; break;
			}
		}
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_up      (const sge::gui::events::mouse_event &me) {
		dump(me, "release");
		{
			sge::scoped_lock<sge::vertex_buffer_ptr> _lock(cuvb);
			sge::vertex_buffer::iterator it = cuvb->begin();
			switch (me.pressed) {
				case sge::gui::events::mouse_event::RIGHT:
					++it;
				case sge::gui::events::mouse_event::LEFT:
					(++it)->diffuse() = sge::colors::white;
			}
		}
		return sge::gui::inputprocessor::response_continue;
	}
	sge::gui::inputprocessor::response inject_mouse_wheel   (const sge::gui::events::mouse_wheel_event &me) { dump(me, (me.direction == sge::gui::events::mouse_wheel_event::UP) ? "UP" : "DOWN"); return sge::gui::inputprocessor::response_continue; }
	sge::gui::inputprocessor::response inject_mouse_click   (const sge::gui::events::mouse_event &me) { dump(me, pressed_button(me)+" CLICK"); return sge::gui::inputprocessor::response_continue; }
	sge::gui::inputprocessor::response inject_mouse_dblclick(const sge::gui::events::mouse_event &me) { dump(me, pressed_button(me)+" DOUBLE CLICK"); return sge::gui::inputprocessor::response_continue; }
};

int main()
try
{
	std::srand(std::time(0));
	bool running = true;
	sge::plugin_manager pm;

	const sge::plugin<sge::renderer_system>::ptr_type renderer_plugin = pm.get_plugin<sge::renderer_system>().load();
	const sge::plugin<sge::input_system>::ptr_type input_plugin = pm.get_plugin<sge::input_system>().load();

	const sge::renderer_system_ptr rs(renderer_plugin->get()());

	const sge::renderer_parameters param(sge::display_mode(800,600,sge::bit_depth::depth32,100), true);
	const sge::renderer_ptr rend = rs->create_renderer(param);

	const sge::input_system_ptr is(input_plugin->get()(rend->get_window()));

	const sge::plugin<sge::image_loader>::ptr_type image_loader_plugin = pm.get_plugin<sge::image_loader>().load();
	const sge::image_loader_ptr pl(image_loader_plugin->get()());

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	boost::signals::scoped_connection cb(is->register_callback(
		if_(bind(&sge::key_type::code, bind(&sge::key_pair::key, boost::lambda::_1)) == sge::kc::key_escape)
			[var(running)=false])
	);

	sge::vertex_buffer_ptr bgvb, cuvb;
	sge::index_buffer_ptr  bgib, cuib;

	{
		const sge::index_buffer::value_type indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		bgib = rend->create_index_buffer(6, sge::resource_flags::default_, indices);
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
		it->diffuse() = sge::colors::white; ++it;
		it->diffuse() = sge::colors::white; ++it;
		it->diffuse() = sge::colors::white;
	}

	sge::key_state_tracker ks(is);
	sge::gui::inputprocessor ip(is);
	std::cout << "created ip" << std::endl;
	myIA ia(cuvb);
	std::cout << "created ia" << std::endl;
	ia.inputprocessor_attach(ip);
	std::cout << "attached ia" << std::endl;

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

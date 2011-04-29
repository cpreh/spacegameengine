/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


/**
	Example description:

	Environment:
	Shows a black background with an fps counter at the top right and an
	instructional text at the top right of the screen. Uses a viewport
	that adapts to the window size.

	Purpose:
	Initially, a line is created from the current cursor position to the
	current cursor position. On a cursor move event, the last line's end
	point is updated to the current cursor position. On a button click,
	a new line is appended to the last line. The color changes smoothly
	from blue to red.

	This example shows the usage of:

	- sge::line_drawer::object in general (2D only)
	- font loading and display
	- viewport::fill_on_resize
	- fps counter
	- font::text::draw
	- Usage of sge::input::cursor
 */

#include <sge/config/media_path.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text/align_h.hpp>
#include <sge/font/text/align_v.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/string.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/time/frames_counter.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/text.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

namespace
{
// The line drawer currently only accepts three-dimensional points for
// it's lines since it can be used to draw lines in "world space",
// too. In this example, we're just going to show the two-dimensional
// capabilities, so here's a function converting a 2D cursor position
// to a 3D position by just appending a 0 at the end.
sge::renderer::vector3 const
cursor_position_to_vector3(
	sge::input::cursor::position const &p)
{
	return 
		fcppt::math::vector::construct(
			fcppt::math::vector::structure_cast<sge::renderer::vector2>(
				p),
			static_cast<sge::renderer::scalar>(
				0));
}

class follows_cursor
{
FCPPT_NONCOPYABLE(
	follows_cursor);
public:
	explicit
	follows_cursor(
		sge::line_drawer::object &_line_drawer,
		sge::input::cursor::object &_cursor)
	:
		line_drawer_(
			_line_drawer),
		// Register a move callback (which uses absolute positions!) and a
		// button callback
		move_connection_(
			_cursor.move_callback(
				std::tr1::bind(
					&follows_cursor::move_callback,
					this,
					std::tr1::placeholders::_1))),
		click_connection_(
			_cursor.button_callback(
				std::tr1::bind(
					&follows_cursor::click_callback,
					this,
					std::tr1::placeholders::_1)))
	{

	}
private:
	sge::line_drawer::object &line_drawer_;	
	fcppt::signal::scoped_connection 
		move_connection_,
		click_connection_;

	void
	move_callback(
		sge::input::cursor::move_event const &e)
	{
		// To change the line drawer's geometry, we have to create a lock,
		// there's no other way
		sge::line_drawer::scoped_lock lock(
			line_drawer_);

		FCPPT_ASSERT(
			!lock.value().empty());

		// Then we can freely (!) change everything. When unlock is called
		// (in the lock's destructor), all the geometry will be updated at
		// once.
		lock.value().back() = 
			sge::line_drawer::line(
				lock.value().back().begin(),
				cursor_position_to_vector3(
					e.position()),
				lock.value().back().begin_color(),
				lock.value().back().end_color());
	}

	void
	click_callback(
		sge::input::cursor::button_event const &e)
	{
		if(!e.pressed())
			return;

		// Same as above
		sge::line_drawer::scoped_lock lock(
			line_drawer_);

		FCPPT_ASSERT(
			!lock.value().empty());

		lock.value().push_back(
			sge::line_drawer::line(
				lock.value().back().end(),
				lock.value().back().end(),
				lock.value().back().end_color(),
				lock.value().back().begin_color()));
	}
};
}

int 
main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge line drawer example"),
					sge::window::dim(
						1024,
						768))))
		(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::fill_on_resize()))
		(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::mouse_collector) 
					| sge::systems::input_helper::cursor_demuxer 
					| sge::systems::input_helper::keyboard_collector,
				sge::systems::cursor_option_field::null()))
		(sge::systems::parameterless::font));

	bool running = 
		true;

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::font::metrics_ptr const font_metrics(
		sys.font_system().create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(
				30)));

	sge::font::text::drawer_3d font_drawer(
		sys.renderer(),
		sge::image::colors::red());

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color
					= sge::image::colors::black()));

	sge::time::frames_counter frames_counter;

	sge::line_drawer::object line_drawer(
		sys.renderer());

	// Create an initial line
	{
		sge::line_drawer::scoped_lock lock(
			line_drawer);

		lock.value().push_back(
			sge::line_drawer::line(
				cursor_position_to_vector3(
					sys.cursor_demuxer().position()),
				cursor_position_to_vector3(
					sys.cursor_demuxer().position()),
				sge::image::colors::red(),
				sge::image::colors::blue()));
	}

	::follows_cursor follows_cursor(
		line_drawer,
		sys.cursor_demuxer());

	while(
		running)
	{
		sys.window().dispatch();

		frames_counter.update();

		sge::renderer::scoped_block const block(
			sys.renderer());

		// This function sets up an orthographic projection and calls
		// render. It's just a wrapper.
		sge::line_drawer::render_to_screen(
			sys.renderer(),
			line_drawer);

		sge::font::text::draw(
			*font_metrics,
			font_drawer,
			SGE_FONT_TEXT_LIT("Press the left mouse button to set a point"),
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::font::rect::dim>(
					sge::renderer::active_target(
						sys.renderer()
					).viewport().get().size())),
			sge::font::text::align_h::left,
			sge::font::text::align_v::top,
			sge::font::text::flags::none);

		sge::font::text::draw(
			*font_metrics,
			font_drawer,
			sge::font::text::from_fcppt_string(
				frames_counter.frames_str())
			+ SGE_FONT_TEXT_LIT(" fps"),
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::font::rect::dim>(
					sge::renderer::active_target(
						sys.renderer()
					).viewport().get().size())),
			sge::font::text::align_h::right,
			sge::font::text::align_v::top,
			sge::font::text::flags::none);
	}
}
 catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
 catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}

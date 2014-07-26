/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/string.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/systems/cursor_demuxer.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <functional>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
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
		cursor_(
			_cursor),
		// Register a move callback (which uses absolute positions!) and a
		// button callback
		move_connection_(
			_cursor.move_callback(
				std::bind(
					&follows_cursor::move_callback,
					this,
					std::placeholders::_1))),
		click_connection_(
			_cursor.button_callback(
				std::bind(
					&follows_cursor::click_callback,
					this,
					std::placeholders::_1)))
	{

	}
FCPPT_PP_POP_WARNING

	~follows_cursor()
	{
	}
private:
	sge::line_drawer::object &line_drawer_;

	sge::input::cursor::object &cursor_;

	fcppt::signal::scoped_connection
		move_connection_,
		click_connection_;

	void
	move_callback(
		sge::input::cursor::move_event const &e)
	{
		if(!e.position())
			return;
		// To change the line drawer's geometry, we have to create a lock,
		// there's no other way
		sge::line_drawer::scoped_lock lock(
			line_drawer_);

		if(lock.value().empty())
			return;

		// Then we can freely (!) change everything. When unlock is called
		// (in the lock's destructor), all the geometry will be updated at
		// once.
		lock.value().back() =
			sge::line_drawer::line(
				lock.value().back().begin(),
				cursor_position_to_vector3(
					*e.position()),
				sge::image::color::any::object(
					lock.value().back().begin_color()),
				sge::image::color::any::object(
					lock.value().back().end_color()));
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

		if(lock.value().empty())
		{
			sge::input::cursor::optional_position const pos(
				cursor_.position());

			if(!pos)
				return;

			sge::renderer::vector3 const pos3(
				cursor_position_to_vector3(
					*pos));

			lock.value().push_back(
				sge::line_drawer::line(
					pos3,
					pos3,
					sge::image::color::predef::red(),
					sge::image::color::predef::blue()));
		}
		else
			lock.value().push_back(
				sge::line_drawer::line(
					lock.value().back().end(),
					lock.value().back().end(),
					sge::image::color::any::object(
						lock.value().back().end_color()),
					sge::image::color::any::object(
						lock.value().back().begin_color())));
	}
};
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		boost::mpl::vector4<
			sge::systems::with_font,
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::cursor_demuxer,
					sge::systems::keyboard_collector
				>
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("sge line drawer example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	sge::font::object_unique_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
				.family(
					FCPPT_TEXT("sans")
				)
		)
	);

	sge::timer::frames_counter frames_counter;

	sge::line_drawer::object line_drawer(
		sys.renderer_device_ffp());

	::follows_cursor follows_cursor(
		line_drawer,
		sys.cursor_demuxer());

	while(
		sys.window_system().poll())
	{

		frames_counter.update();

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target());

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()));

		// This function sets up an orthographic projection and calls
		// render. It's just a wrapper.
		sge::line_drawer::render_to_screen(
			sys.renderer_device_ffp(),
			scoped_block.get(),
			line_drawer);

		sge::font::vector const font_pos(
			sge::font::vector::null());

		sge::font::align_h::max_width const font_width(
			fcppt::cast::size<
				sge::font::unit
			>(
				fcppt::cast::to_signed(
					sge::renderer::target::viewport_size(
						sys.renderer_device_ffp().onscreen_target()
					).w()
				)
			)
		);

		sge::font::draw::simple(
			sys.renderer_device_ffp(),
			scoped_block.get(),
			*font,
			SGE_FONT_LIT("Press the left mouse button to set a point"),
			sge::font::text_parameters(
				sge::font::align_h::left(
					font_width
				)
			),
			font_pos,
			sge::image::color::predef::red(),
			sge::renderer::texture::emulate_srgb::yes);

		sge::font::draw::simple(
			sys.renderer_device_ffp(),
			scoped_block.get(),
			*font,
			sge::font::from_fcppt_string(
				frames_counter.frames_str())
			+ SGE_FONT_LIT(" fps"),
			sge::font::text_parameters(
				sge::font::align_h::right(
					font_width
				)
			),
			font_pos,
			sge::image::color::predef::red(),
			sge::renderer::texture::emulate_srgb::yes
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}

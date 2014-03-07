/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/console/font_color.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/muxing.hpp>
#include <sge/console/muxing_streambuf.hpp>
#include <sge/console/object.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/log_location.hpp>
#include <sge/input/cursor/button_code_to_string.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/manager.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/input/cursor/scroll_code_to_string.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/manager.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/key_code_to_string.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/mouse/axis_code_to_string.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_code_to_string.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/manager.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <functional>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::string
output_optional_string(
	fcppt::optional_string const &
);

fcppt::string
output_optional_position(
	sge::input::cursor::optional_position const &
);

void
cursor_discover(
	sge::input::cursor::discover_event const &
);

void
cursor_remove(
	sge::input::cursor::remove_event const &
);

void
cursor_button(
	sge::input::cursor::object &,
	sge::input::cursor::button_event const &
);

void
cursor_move(
	sge::input::cursor::object &,
	sge::input::cursor::move_event const &
);

void
cursor_scroll(
	sge::input::cursor::object &,
	sge::input::cursor::scroll_event const &
);

void
joypad_discover(
	sge::input::joypad::discover_event const &
);

void
joypad_remove(
	sge::input::joypad::remove_event const &
);

void
joypad_absolute_axis(
	sge::input::joypad::device &,
	sge::input::joypad::absolute_axis_event const &
);

void
joypad_button(
	sge::input::joypad::device &,
	sge::input::joypad::button_event const &
);

void
joypad_relative_axis(
	sge::input::joypad::device &,
	sge::input::joypad::relative_axis_event const &
);

void
keyboard_discover(
	sge::input::keyboard::discover_event const &
);

void
keyboard_remove(
	sge::input::keyboard::remove_event const &
);

void
keyboard_char(
	sge::input::keyboard::device &,
	sge::input::keyboard::char_event const &
);

void
keyboard_key(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_event const &
);

void
keyboard_key_repeat(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_repeat_event const &
);

void
mouse_discover(
	sge::input::mouse::discover_event const &
);

void
mouse_remove(
	sge::input::mouse::remove_event const &
);

void
mouse_axis(
	sge::input::mouse::device &,
	sge::input::mouse::axis_event const &
);

void
mouse_button(
	sge::input::mouse::device &,
	sge::input::mouse::button_event const &
);

bool
extract_silent_parameter(
	awl::main::function_context const &
);

std::string const silent_parameter(
	"-silent"
);

struct dummy_event_handler
{
	typedef void result_type;

	template<
		typename Device,
		typename Event
	>
	result_type
	operator()(
		Device &,
		Event const &
	) const;
};

template<
	typename Functor,
	typename Function
>
Functor const
wrap_silent(
	Function const &,
	bool silent
);

void
manage_console_size(
	sge::console::sprite_object &,
	sge::renderer::target::viewport const &
);

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_context
)
try
{
	if(
		_context.argc() > 2
		||
		(
			_context.argc() == 2
			&&
			_context.argv()[1]
			!=
			silent_parameter
		)
	)
	{
		awl::show_error(
			FCPPT_TEXT("You can pass no arguments or -silent to suppress input.")
		);

		return
			awl::main::exit_failure();
	}

	bool const silent(
		extract_silent_parameter(
			_context
		)
	);

	sge::systems::instance<
		boost::mpl::vector4<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector1<
					sge::systems::keyboard_collector
				>
			>,
			sge::systems::with_font
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge input example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
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
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field{
					sge::systems::cursor_option::exclusive
				}
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::input::log_location(),
					silent
					?
						fcppt::log::level::error
					:
						fcppt::log::level::debug
				)
			)
		)
	);

	sge::console::object console(
		SGE_FONT_LIT('/')
	);

	sge::console::muxing_streambuf<
		fcppt::io::ostream::char_type,
		fcppt::io::ostream::traits_type
	> muxing_streambuf(
		fcppt::io::cout(),
		console,
		sge::console::muxing::enabled
	);

	sge::font::object_scoped_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
		)
	);

	sge::console::gfx console_gfx(
		console,
		sys.renderer_device_ffp(),
		sge::console::font_color(
			sge::image::color::predef::white()
		),
		*font,
		sys.keyboard_collector(),
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.pos(
				sge::console::sprite_object::vector::null()
			)
			.size(
				sge::console::sprite_object::dim::null()
			)
		),
		sge::console::output_line_limit(
			200u
		)
	);

	console_gfx.active(
		true
	);

	console_gfx.input_active(
		false
	);

	fcppt::signal::scoped_connection const console_resize_con(
		sys.viewport_manager().manage_callback(
			std::bind(
				manage_console_size,
				std::ref(
					console_gfx.background_sprite()
				),
				std::placeholders::_1
			)
		)
	);

	fcppt::io::cout()
		<< std::boolalpha;

	sge::input::cursor::manager const cursor_manager(
		sys.input_processor(),
		sge::input::cursor::discover_callback(
			::cursor_discover
		),
		sge::input::cursor::remove_callback(
			::cursor_remove
		),
		wrap_silent<
			sge::input::cursor::manager::button_callback
		>(
			::cursor_button,
			silent
		),
		wrap_silent<
			sge::input::cursor::manager::move_callback
		>(
			::cursor_move,
			silent
		),
		wrap_silent<
			sge::input::cursor::manager::scroll_callback
		>(
			::cursor_scroll,
			silent
		)
	);

	sge::input::joypad::manager const joypad_manager(
		sys.input_processor(),
		sge::input::joypad::discover_callback(
			::joypad_discover
		),
		sge::input::joypad::remove_callback(
			::joypad_remove
		),
		wrap_silent<
			sge::input::joypad::manager::absolute_axis_callback
		>(
			::joypad_absolute_axis,
			silent
		),
		wrap_silent<
			sge::input::joypad::manager::button_callback
		>(
			::joypad_button,
			silent
		),
		wrap_silent<
			sge::input::joypad::manager::relative_axis_callback
		>(
			::joypad_relative_axis,
			silent
		)
	);

	sge::input::keyboard::manager const keyboard_manager(
		sys.input_processor(),
		sge::input::keyboard::discover_callback(
			::keyboard_discover
		),
		sge::input::keyboard::remove_callback(
			::keyboard_remove
		),
		wrap_silent<
			sge::input::keyboard::manager::char_callback
		>(
			::keyboard_char,
			silent
		),
		wrap_silent<
			sge::input::keyboard::manager::key_callback
		>(
			::keyboard_key,
			silent
		),
		wrap_silent<
			sge::input::keyboard::manager::key_repeat_callback
		>(
			::keyboard_key_repeat,
			silent
		)
	);

	sge::input::mouse::manager const mouse_manager(
		sys.input_processor(),
		sge::input::mouse::discover_callback(
			::mouse_discover
		),
		sge::input::mouse::remove_callback(
			::mouse_remove
		),
		wrap_silent<
			sge::input::mouse::manager::axis_callback
		>(
			::mouse_axis,
			silent
		),
		wrap_silent<
			sge::input::mouse::manager::button_callback
		>(
			::mouse_button,
			silent
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::timer::scoped_frame_limiter const limiter(
			sge::renderer::display_mode::desired_fps(
				sys.renderer_device_ffp().display_mode()
			)
		);

		sge::renderer::context::scoped_ffp const scoped_ffp(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		scoped_ffp.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
			)
		);

		console_gfx.render(
			scoped_ffp.get()
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_exception
)
{
	awl::show_error(
		_exception.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_exception
)
{
	awl::show_error_narrow(
		_exception.what()
	);

	return
		awl::main::exit_failure();
}

namespace
{

fcppt::string
output_optional_string(
	fcppt::optional_string const &_name
)
{
	return
		_name
		?
			*_name
		:
			fcppt::string(
				FCPPT_TEXT("unnamed")
			)
		;
}

fcppt::string
output_optional_position(
	sge::input::cursor::optional_position const &_position
)
{
	return
		_position
		?
			fcppt::insert_to_fcppt_string(
				*_position
			)
		:
			fcppt::string(
				FCPPT_TEXT("none")
			)
		;
}

void
cursor_discover(
	sge::input::cursor::discover_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
cursor_remove(
	sge::input::cursor::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
cursor_button(
	sge::input::cursor::object &_object,
	sge::input::cursor::button_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_button: ")
		<< &_object
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::cursor::button_code_to_string(
			_event.button_code()
		)
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
cursor_move(
	sge::input::cursor::object &_object,
	sge::input::cursor::move_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_move: ")
		<< &_object
		<< FCPPT_TEXT("\n\tposition: ")
		<< output_optional_position(
			_event.position()
		)
		<< FCPPT_TEXT('\n');
}

void
cursor_scroll(
	sge::input::cursor::object &_object,
	sge::input::cursor::scroll_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("cursor_scroll: ")
		<< &_object
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::cursor::scroll_code_to_string(
			_event.code()
		)
		<< FCPPT_TEXT("\n\tdelta: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
joypad_discover(
	sge::input::joypad::discover_event const &_event
)
{
	sge::input::joypad::info const info(
		_event.get().info()
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT(", ")
		<< info.name()
		<< FCPPT_TEXT(", ")
		<< info.unique_id()
		<< FCPPT_TEXT('\n');

	{
		sge::input::joypad::absolute_axis_info_container::vector const &absolute_axes(
			info.absolute_axes().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tabsolute axes: ")
			<< absolute_axes.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::absolute_axis_info const &axis_info
			:
			absolute_axes
		)
			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::joypad::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT("\n\t\tmin: ")
				<< axis_info.min()
				<< FCPPT_TEXT("\n\t\tmax: ")
				<< axis_info.max()
				<< FCPPT_TEXT('\n');
	}

	{
		sge::input::joypad::relative_axis_info_container::vector const &relative_axes(
			info.relative_axes().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\trelative axes: ")
			<< relative_axes.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::relative_axis_info const &axis_info
			:
			relative_axes
		)
			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::joypad::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT('\n');
	}

	{
		sge::input::joypad::button_info_container::vector const &buttons(
			info.buttons().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tbuttons: ")
			<< buttons.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::joypad::button_info const &button_info
			:
			buttons
		)
			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					button_info.name()
				)
				<< FCPPT_TEXT('\n');
	}

}

void
joypad_remove(
	sge::input::joypad::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
joypad_absolute_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::absolute_axis_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_absolute_axis: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::joypad::axis_code_to_string(
			_event.axis().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.axis().id()
		<< FCPPT_TEXT("\n\tvalue: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
joypad_button(
	sge::input::joypad::device &_device,
	sge::input::joypad::button_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_button: ")
		<< &_device
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.button_id()
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
joypad_relative_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::relative_axis_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_relative_axis: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::joypad::axis_code_to_string(
			_event.axis().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.axis().id()
		<< FCPPT_TEXT("\n\tvalue: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
keyboard_discover(
	sge::input::keyboard::discover_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
keyboard_remove(
	sge::input::keyboard::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
keyboard_char(
	sge::input::keyboard::device &_device,
	sge::input::keyboard::char_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_char: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcharacter_value: ")
		<< static_cast<
			unsigned long
		>(
			_event.character()
		)
		<< FCPPT_TEXT("\n\tchar: ")
		<< fcppt::from_std_wstring(
			std::wstring(
				1u,
				_event.character()
			)
		)
		<< FCPPT_TEXT("\n\trepeated: ")
		<< _event.repeated()
		<< FCPPT_TEXT('\n');
}

void
keyboard_key(
	sge::input::keyboard::device &_device,
	sge::input::keyboard::key_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_key: ")
		<< &_device
		<< FCPPT_TEXT("\n\tkey: ")
		<< sge::input::keyboard::key_code_to_string(
			_event.key_code()
		)
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

void
keyboard_key_repeat(
	sge::input::keyboard::device &_device,
	sge::input::keyboard::key_repeat_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("keyboard_key_repeat: ")
		<< &_device
		<< FCPPT_TEXT("\n\tkey: ")
		<< sge::input::keyboard::key_code_to_string(
			_event.key_code()
		)
		<< FCPPT_TEXT('\n');
}

void
mouse_discover(
	sge::input::mouse::discover_event const &_event
)
{
	sge::input::mouse::info const info(
		_event.get().info()
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT(", ")
		<< info.name()
		<< FCPPT_TEXT('\n');

	{
		sge::input::mouse::axis_info_container::vector const &axes(
			info.axes().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\taxes: ")
			<< axes.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::mouse::axis_info const &axis_info
			:
			axes
		)
			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					axis_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::mouse::axis_code_to_string(
					axis_info.code()
				)
				<< FCPPT_TEXT('\n');
	}

	{
		sge::input::mouse::button_info_container::vector const &buttons(
			info.buttons().get()
		);

		fcppt::io::cout()
			<< FCPPT_TEXT("\tbuttons: ")
			<< buttons.size()
			<< FCPPT_TEXT('\n');

		for(
			sge::input::mouse::button_info const &button_info
			:
			buttons
		)
			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					button_info.name()
				)
				<< FCPPT_TEXT("\n\t\tcode: ")
				<< sge::input::mouse::button_code_to_string(
					button_info.code()
				)
				<< FCPPT_TEXT('\n');
	}
}

void
mouse_remove(
	sge::input::mouse::remove_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
mouse_axis(
	sge::input::mouse::device &_device,
	sge::input::mouse::axis_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_axis: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::mouse::axis_code_to_string(
			_event.axis().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.axis().id()
		<< FCPPT_TEXT("\n\tvalue: ")
		<< _event.value()
		<< FCPPT_TEXT('\n');
}

void
mouse_button(
	sge::input::mouse::device &_device,
	sge::input::mouse::button_event const &_event
)
{
	fcppt::io::cout()
		<< FCPPT_TEXT("mouse_button: ")
		<< &_device
		<< FCPPT_TEXT("\n\tcode: ")
		<< sge::input::mouse::button_code_to_string(
			_event.button().code()
		)
		<< FCPPT_TEXT("\n\tid: ")
		<< _event.button().id()
		<< FCPPT_TEXT("\n\tpressed: ")
		<< _event.pressed()
		<< FCPPT_TEXT('\n');
}

bool
extract_silent_parameter(
	awl::main::function_context const &_context
)
{
	return
		_context.argc() == 2
		&&
		_context.argv()[1]
		==
		silent_parameter
		;
}

template<
	typename Device,
	typename Event
>
typename dummy_event_handler::result_type
dummy_event_handler::operator()(
	Device &,
	Event const &
) const
{
}

template<
	typename Functor,
	typename Function
>
Functor const
wrap_silent(
	Function const &_function,
	bool const _silent
)
{
	return
		_silent
		?
			Functor(
				dummy_event_handler()
			)
		:
			Functor(
				_function
			)
		;
}

void
manage_console_size(
	sge::console::sprite_object &_sprite,
	sge::renderer::target::viewport const &_viewport
)
{
	_sprite.size(
		fcppt::math::dim::structure_cast<
			sge::console::sprite_object::dim
		>(
			_viewport.get().size()
		)
	);
}

}

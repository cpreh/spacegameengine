#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/manager.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <example_main.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <fcppt/string.hpp>
#include <sge/input/info/optional_string.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/system.hpp>
#include <sge/font/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/ref.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <fcppt/io/ostringstream.hpp>

namespace
{
fcppt::string const
output_optional_string(
	sge::input::info::optional_string const &_name
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

void
joypad_discover(
	sge::input::joypad::discover_event const &_event,
	sge::font::draw::static_text &_text
)
{
	sge::input::joypad::info const info(
		_event.get().info()
	);

	_text.color(
		sge::image::colors::green());

	_text.string(
		sge::font::from_fcppt_string(
			info.name().get()));

	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_discover: ")
		<< &_event.get()
		<< FCPPT_TEXT(", ")
		<< info.name()
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
			sge::input::joypad::absolute_axis_info_container::vector::const_iterator it(
				absolute_axes.begin()
			);
			it != absolute_axes.end();
			++it
		)
		{
			sge::input::joypad::absolute_axis_info const &axis_info(
				*it
			);

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
			sge::input::joypad::relative_axis_info_container::vector::const_iterator it(
				relative_axes.begin()
			);
			it != relative_axes.end();
			++it
		)
		{
			sge::input::joypad::relative_axis_info const &axis_info(
				*it
			);

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
			sge::input::joypad::button_info_container::vector::const_iterator it(
				buttons.begin()
			);
			it != buttons.end();
			++it
		)
		{
			sge::input::joypad::button_info const &button_info(
				*it
			);

			fcppt::io::cout()
				<< FCPPT_TEXT("\t\tname: ")
				<< output_optional_string(
					button_info.name()
				)
				<< FCPPT_TEXT('\n');
		}
	}

}

void
joypad_remove(
	sge::input::joypad::remove_event const &_event,
	sge::font::draw::static_text &_text
)
{
	_text.string(
		sge::font::from_fcppt_string(
			FCPPT_TEXT("no joypad connected")));
	_text.color(
		sge::image::colors::red());

	fcppt::io::cout()
		<< FCPPT_TEXT("joypad_remove: ")
		<< &_event.get()
		<< FCPPT_TEXT('\n');
}

void
joypad_absolute_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::absolute_axis_event const &_event,
	sge::font::draw::static_text &_text
)
{
	fcppt::io::ostringstream ss;

	ss
		<< FCPPT_TEXT("absolute axis ")
		<< _event.axis().id()
		<< FCPPT_TEXT(" (")
		<< output_optional_string(
			_device.info().absolute_axes()[_event.axis().id()].name())
		<< FCPPT_TEXT(")");

	_text.string(
		sge::font::from_fcppt_string(
			ss.str()));
}

void
joypad_relative_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::relative_axis_event const &_event,
	sge::font::draw::static_text &_text
)
{
	fcppt::io::ostringstream ss;

	ss
		<< FCPPT_TEXT("relative axis ")
		<< _event.axis().id()
		<< FCPPT_TEXT(" (")
		<< output_optional_string(
			_device.info().relative_axes()[_event.axis().id()].name())
		<< FCPPT_TEXT(")");

	_text.string(
		sge::font::from_fcppt_string(
			ss.str()));
}

void
joypad_button(
	sge::input::joypad::device &_device,
	sge::input::joypad::button_event const &_event,
	sge::font::draw::static_text &_text
)
{
	if (!_event.pressed()) return;
	fcppt::io::ostringstream ss;

	ss
		<< FCPPT_TEXT("button ")
		<< _event.button_id()
		<< FCPPT_TEXT(" (")
		<< output_optional_string(
			_device.info().buttons()[_event.button_id()].name())
		<< FCPPT_TEXT(")");

	_text.string(
		sge::font::from_fcppt_string(
			ss.str()));
}
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_context
)
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge control scheme example")
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
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
		(
			sge::systems::font()
		)
	);

	sge::font::object_scoped_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
		)
	);

	sge::font::draw::static_text joypad_infotext(
		sys.renderer(),
		*font,
		SGE_FONT_LIT(
			"no gamepad connected"
		),
		sge::font::text_parameters(
			sge::font::align_h::left
		),
		sge::font::vector(
			0,
			0
		),
		sge::image::colors::red()
	);

	sge::font::draw::static_text event_infotext(
		sys.renderer(),
		*font,
		SGE_FONT_LIT(
			"press some joypad button"
		),
		sge::font::text_parameters(
			sge::font::align_h::left
		),
		sge::font::vector(
			0,
			100
		),
		sge::image::colors::white()
	);

	sge::input::joypad::manager const joypad_manager(
		sys.input_processor(),
		sge::input::joypad::discover_callback(
				std::tr1::bind(
					&::joypad_discover,
					std::tr1::placeholders::_1,
					fcppt::ref(
						joypad_infotext))
		),
		sge::input::joypad::remove_callback(
				std::tr1::bind(
					&::joypad_remove,
					std::tr1::placeholders::_1,
					fcppt::ref(
						joypad_infotext))
		),
		sge::input::joypad::manager::absolute_axis_callback(
			std::tr1::bind(
				&::joypad_absolute_axis,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					event_infotext))
		),
		sge::input::joypad::manager::button_callback(
			std::tr1::bind(
				&::joypad_button,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					event_infotext))
		),
		sge::input::joypad::manager::relative_axis_callback(
			std::tr1::bind(
				&::joypad_relative_axis,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					event_infotext))
		)
	);

	while(
		sys.window_system().next()
	)
	{
		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
		);

		event_infotext.draw(
			scoped_block.get()
		);

		joypad_infotext.draw(
			scoped_block.get()
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}

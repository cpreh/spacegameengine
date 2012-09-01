#include <sge/config/media_path.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/info/optional_string.hpp>
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
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_stream.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/insert_unique_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <example_main.hpp>
#include <fcppt/config/external_end.hpp>
#include <sge/font/string.hpp>


namespace
{
sge::font::string const
disconnected_text(
	sge::font::from_fcppt_string(
		FCPPT_TEXT("no gamepad connected")));

sge::font::string const
unassigned_text(
	sge::font::from_fcppt_string(
		FCPPT_TEXT("<unassigned>")));

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
click_callback(
	sge::input::cursor::object const &_cursor,
	sge::input::cursor::button_event const &_event
)
{
	if (!_event.pressed())
		return;

	sge::input::cursor::optional_position const pos(
		_cursor.position());

	if (!pos)
		return;

	fcppt::io::cerr()
		<< (*pos)
		<< FCPPT_TEXT("\n");
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
			info.name().get()
			+ FCPPT_TEXT(", id: ")
			+ info.unique_id().get()
			));

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
		disconnected_text);
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
	if(
		_context.argc() > 2
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("usage: ")
			<< _context.argv()[0]
			<< FCPPT_TEXT(" [control scheme]");

		return
			awl::main::exit_failure();
	}

	boost::filesystem::path const
		control_scheme_path(
			(_context.argc() == 2)
			?
				_context.argv()[1]
			:
				sge::config::media_path() /
				FCPPT_TEXT("example_controls.json"));

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
				)
					| sge::systems::input_helper::cursor_demuxer
					| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::font()
		)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	sge::font::object_scoped_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
			.family(
				FCPPT_TEXT("monospace"))
			.ttf_size(
				sge::font::ttf_size(
					20))
		)
	);

	sge::font::draw::static_text joypad_infotext(
		sys.renderer(),
		*font,
		disconnected_text,
		sge::font::text_parameters(
			sge::font::align_h::left
		),
		sge::font::vector(
			0,
			0
		),
		sge::image::colors::red()
	);

	fcppt::io::ifstream
		ifs(
			control_scheme_path);

	sge::parse::json::object result;

	if(
		!sge::parse::json::parse_stream(
			ifs,
			result
		)
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Couldn't parse controls file.");

		return awl::main::exit_failure();
	}

	typedef
	boost::ptr_vector<
		sge::font::draw::static_text
	>
	text_vector;

	text_vector control_labels;
	text_vector control_texts;
	text_vector::iterator active_text;

	sge::parse::json::array	controls =
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			result.members,
			FCPPT_TEXT("controls"));

	{
		int ypos = 0;
		int label_width = 500;

		for(
			sge::parse::json::element_vector::const_iterator current_control =
				controls.elements.begin();
			current_control !=
				controls.elements.end();
			++current_control)
		{
			fcppt::string const control_name(
				sge::parse::json::find_and_convert_member<fcppt::string>(
					sge::parse::json::get<sge::parse::json::object const>(
						*current_control),
					sge::parse::json::path(
						FCPPT_TEXT("name"))));

			fcppt::string const control_type(
				sge::parse::json::find_and_convert_member<fcppt::string>(
					sge::parse::json::get<sge::parse::json::object const>(
						*current_control),
					sge::parse::json::path(
						FCPPT_TEXT("type"))));

			fcppt::container::ptr::insert_unique_ptr(
				control_labels,
				control_labels.end(),
				fcppt::make_unique_ptr<
					sge::font::draw::static_text
				>(
					fcppt::ref(sys.renderer()),
					fcppt::ref(*font),
					sge::font::from_fcppt_string(
						control_name
						+ FCPPT_TEXT("(")
						+ control_type
						+ FCPPT_TEXT("): ")
					),
					sge::font::text_parameters(
						sge::font::align_h::left
					),
					sge::font::vector(
						0,
						40 +
						30 *
						ypos
					),
					sge::image::colors::gray()
				)
			);

			fcppt::container::ptr::insert_unique_ptr(
				control_texts,
				control_texts.end(),
				fcppt::make_unique_ptr<
					sge::font::draw::static_text
				>(
					fcppt::ref(sys.renderer()),
					fcppt::ref(*font),
					unassigned_text,
					sge::font::text_parameters(
						sge::font::align_h::left
					),
					sge::font::vector(
						label_width + 10,
						40 +
						30 *
						(ypos++)
					),
					sge::image::colors::gray()
				)
			);
		}
	}
	active_text =
		control_texts.begin();

	fcppt::signal::scoped_connection const click_connection(
		sys.cursor_demuxer().button_callback(
			std::tr1::bind(
				::click_callback,
				fcppt::cref(
					sys.cursor_demuxer()),
				std::tr1::placeholders::_1
			)
		)
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
					*control_texts.begin()))
		),
		sge::input::joypad::manager::button_callback(
			std::tr1::bind(
				&::joypad_button,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					*control_texts.begin()))
		),
		sge::input::joypad::manager::relative_axis_callback(
			std::tr1::bind(
				&::joypad_relative_axis,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					*control_texts.begin()))
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

		active_text->color(
			sge::image::colors::white());

		for(
			text_vector::iterator it =
				control_labels.begin();
			it !=
				control_labels.end();
			++it
		)
			it->draw(
				scoped_block.get());

		for(
			text_vector::iterator it =
				control_texts.begin();
			it !=
				control_texts.end();
			++it
		)
			it->draw(
				scoped_block.get());

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

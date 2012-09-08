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
#include <sge/font/string.hpp>
#include <sge/font/rect.hpp>
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
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tool_main.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{
namespace control_type
{
enum type {
	scalar,
	bool_
};
}

namespace input_type
{
enum type {
	button,
	absolute_axis,
	relative_axis
};
}

struct
device
{
	fcppt::string name_;
	fcppt::string id_;

device()
{
}

device(
	fcppt::string const &_name,
	fcppt::string const &_id
)
:
	name_(
		_name),
	id_(
		_id)
{
}
};

struct
input
{
	input()
	{
	}

	input(
		::input_type::type _type,
		int _id
	)
	:
		type_(
			_type),
		id_(
			_id)
	{
	}

	::input_type::type type_;
	int id_;
};

struct
control_mapping
{
	control_mapping()
	{
	}

	control_mapping(
		fcppt::string _name,
		::control_type::type _type,
		::input _input
	)
	:
		name_(
			_name),
		type_(
			_type),
		input_(
			_input)
	{
	}

	fcppt::string name_;
	::control_type::type type_;
	::input input_;

};

typedef
std::vector
<
	::control_mapping
>
controls_vector;

struct
control_config
{
	::device device_;
	::controls_vector controls_;

	void
	device(
		::device _device)
	{
		device_ =
			_device;
	}
};

typedef
boost::ptr_vector<
	sge::font::draw::static_text
>
text_vector;

sge::font::string const
disconnected_text(
	sge::font::from_fcppt_string(
		FCPPT_TEXT("no gamepad connected")));

sge::font::string const
save_text(
	sge::font::from_fcppt_string(
		FCPPT_TEXT("Save & Exit")));

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
save_config()
{
	fcppt::io::cerr() <<
		FCPPT_TEXT("Would save now!");
}

void
click_callback(
	sge::input::cursor::object const &_cursor,
	::control_config &_model,
	::text_vector &_texts,
	::text_vector::iterator &_active,
	sge::font::draw::static_text const &_save_button,
	sge::input::cursor::button_event const &_event
)
{
	if (!_event.pressed())
		return;

	sge::input::cursor::optional_position const pos(
		_cursor.position());

	if (!pos)
		return;

	sge::font::rect save_box(
		_save_button.rect().pos() + _save_button.pos(),
		_save_button.rect().size());
	if (
		fcppt::math::box::contains_point(
			save_box,
			*pos)
	)
	{
		save_config();
		//unreachable
	}

	for (
		::text_vector::iterator text =
			_texts.begin();
		text !=
			_texts.end();
		++text)
	{
		sge::font::rect actual_box(
			text->rect().pos() + text->pos(),
			text->rect().size());

		if (
			fcppt::math::box::contains_point(
				actual_box,
				*pos)
		)
			_active = text;

		text->color(
			sge::image::colors::gray());
	}
	_active->color(
		sge::image::colors::white());
}

void
joypad_discover(
	sge::input::joypad::discover_event const &_event,
	::control_config &_model,
	sge::font::draw::static_text &_text
)
{
	sge::input::joypad::info const info(
		_event.get().info()
	);

	_text.color(
		sge::image::colors::green());

	fcppt::string const name(
		info.name().get());

	fcppt::string const id(
		info.unique_id().get());

	_model.device(
		::device(
			name,
			id));

	_text.string(
		sge::font::from_fcppt_string(
			name
			+ FCPPT_TEXT(", id: ")
			+ id
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
	::control_config &_model,
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
	::control_config &_model,
	::text_vector::iterator &_text
)
{
	sge::input::joypad::axis_value value = 
		_event.value();

	if (value == 0)
		return;

	fcppt::io::ostringstream ss;

	ss
		<< FCPPT_TEXT("absolute axis ")
		<<
			(
				(value < 0)
				?
				FCPPT_TEXT('-')
				:
				FCPPT_TEXT('+')
			)
		<< _event.axis().id()
		<< FCPPT_TEXT(" (")
		<< output_optional_string(
			_device.info().absolute_axes()[_event.axis().id()].name())
		<< FCPPT_TEXT(")");

	_text->string(
		sge::font::from_fcppt_string(
			ss.str()));
}

void
joypad_relative_axis(
	sge::input::joypad::device &_device,
	sge::input::joypad::relative_axis_event const &_event,
	::control_config &_model,
	::text_vector::iterator &_text
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

	_text->string(
		sge::font::from_fcppt_string(
			ss.str()));
}

void
joypad_button(
	sge::input::joypad::device &_device,
	sge::input::joypad::button_event const &_event,
	::control_config &_model,
	::text_vector::iterator &_text
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

	_text->string(
		sge::font::from_fcppt_string(
			ss.str()));
}
}

awl::main::exit_code const
tool_main(
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

	sge::window::dim const
	window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge control scheme example")
					),
					window_dim
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

	::control_config
		model;

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

	sge::font::draw::static_text save_button(
		sys.renderer(),
		*font,
		save_text,
		sge::font::text_parameters(
			sge::font::align_h::left
		),
		sge::font::vector(
			0,
			window_dim.h() - joypad_infotext.rect().h() - 10 //hacky hack
		),
		sge::image::colors::blue()
	);

	fcppt::io::ifstream
		ifs(
			control_scheme_path);

	sge::parse::json::object controls_input;

	if(
		!sge::parse::json::parse_stream(
			ifs,
			controls_input
		)
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Couldn't parse controls file.");

		return awl::main::exit_failure();
	}

	::text_vector control_labels;
	::text_vector control_texts;
	::text_vector::iterator active_text;

	sge::parse::json::array	controls =
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			controls_input.members,
			FCPPT_TEXT("controls"));

	{
		int ypos = 0;
		int label_width = 0;
		int line_height = 0;
		int lines_offset = 40;
		sge::font::vector position;

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

			// model...
			model.controls_.push_back(
				control_mapping(
					control_name,
					control_type == FCPPT_TEXT("bool")
					?
						::control_type::bool_
					:
						::control_type::scalar,
					::input()
				)
			);

			// view...
			position = sge::font::vector(
				0,
				lines_offset +
				line_height *
				ypos
			);

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
					position,
					sge::image::colors::gray()
				)
			);

			label_width =
					15 + control_labels.back().rect().w();

			if(ypos == 0)
				line_height =
					static_cast<int>(
						1.5 * control_labels.back().rect().h());

			position = sge::font::vector(
				label_width + 10,
				lines_offset +
				line_height *
				(ypos++)
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
					position,
					sge::image::colors::gray()
				)
			);

		}
	}

	active_text =
		control_texts.begin();
	active_text->color(
		sge::image::colors::white());

	// TODO don't allow double mappings?

	fcppt::signal::scoped_connection const click_connection(
		sys.cursor_demuxer().button_callback(
			std::tr1::bind(
				::click_callback,
				fcppt::cref(
					sys.cursor_demuxer()),
				fcppt::ref(
					model),
				fcppt::ref(
					control_texts),
				fcppt::ref(
					active_text),
				fcppt::ref(
					save_button),
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
					model),
				fcppt::ref(
					joypad_infotext))
		),
		sge::input::joypad::remove_callback(
			std::tr1::bind(
				&::joypad_remove,
				std::tr1::placeholders::_1,
				fcppt::ref(
					model),
				fcppt::ref(
					joypad_infotext))
		),
		sge::input::joypad::manager::absolute_axis_callback(
			std::tr1::bind(
				&::joypad_absolute_axis,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					model),
				fcppt::ref(
					active_text))
		),
		sge::input::joypad::manager::button_callback(
			std::tr1::bind(
				&::joypad_button,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					model),
				fcppt::ref(
					active_text))
		),
		sge::input::joypad::manager::relative_axis_callback(
			std::tr1::bind(
				&::joypad_relative_axis,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				fcppt::ref(
					model),
				fcppt::ref(
					active_text))
		)
	);

	while(
		sys.window_system().poll()
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

		for(
			::text_vector::iterator it =
				control_labels.begin();
			it !=
				control_labels.end();
			++it
		)
			it->draw(
				scoped_block.get());

		for(
			::text_vector::iterator it =
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

		save_button.draw(
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

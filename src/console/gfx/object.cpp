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


#include <sge/console/exception.hpp>
#include <sge/console/object.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/console/gfx/sprite_object.hpp>
#include <sge/console/gfx/detail/pointed_history.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <locale>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::console::gfx::object::object(
	sge::console::object &_object,
	sge::renderer::device::ffp &_renderer,
	sge::console::gfx::font_color const &_font_color,
	sge::font::object &_font_object,
	sge::input::keyboard::device &_keyboard,
	sge::console::gfx::sprite_object const &_background,
	sge::console::gfx::output_line_limit const _line_limit
)
:
	object_(
		_object
	),
	renderer_(
		_renderer
	),
	font_color_(
		_font_color
	),
	font_object_(
		_font_object
	),
	keyboard_(
		_keyboard
	),
	key_connection_(
		keyboard_.key_callback(
			std::bind(
				&sge::console::gfx::object::key_callback,
				this,
				std::placeholders::_1
			)
		)
	),
	key_repeat_connection_(
		keyboard_.key_repeat_callback(
			std::bind(
				&sge::console::gfx::object::key_action,
				this,
				std::placeholders::_1
			)
		)
	),
	char_connection_(
		_keyboard.char_callback(
			std::bind(
				&sge::console::gfx::object::char_callback,
				this,
				std::placeholders::_1
			)
		)
	),
	error_conn_(
		object_.register_error_callback(
			std::bind(
				&sge::console::gfx::object::error,
				this,
				std::placeholders::_1
			)
		)
	),
	message_conn_(
		object_.register_message_callback(
			std::bind(
				&sge::console::gfx::object::print,
				this,
				std::placeholders::_1
			)
		)
	),
	sprite_buffers_(
		_renderer,
		sge::sprite::buffers::option::dynamic
	),
	sprite_state_(
		_renderer,
		sprite_state_parameters()
	),
	background_(
		_background
	),
	active_(
		false
	),
	input_active_(
		true
	),
	input_line_(),
	input_history_(),
	current_input_(
		input_history_.begin()
	),
	output_lines_(
		static_cast<
			sge::console::gfx::detail::pointed_history::size_type
		>(
			_line_limit.get()
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::console::gfx::object::~object()
{
}

void
sge::console::gfx::object::render(
	sge::renderer::context::ffp &_render_context
)
{
	if(
		background_.texture()
	)
		sge::sprite::process::one(
			_render_context,
			background_,
			sprite_buffers_,
			sprite_state_
		);

	sge::font::unit current_y(
		background_.h()
	);

	if(
		input_active_
	)
		current_y =
			this->render_line(
				_render_context,
				input_line_.edited(
					// This used to be "bool cursor_active" which was controlled by
					// a timer, but due to the unneccessary timer depenceny, this
					// was removed
					true
				),
				current_y
			);

	for(
		sge::console::gfx::detail::pointed_history::const_iterator
			iter(
				output_lines_.point()
			),
			end(
				output_lines_.end()
			);
		iter != end;
		++iter
	)
	{
		current_y =
			this->render_line(
				_render_context,
				*iter,
				current_y
			);

		if(
			current_y < 0
		)
			break;
	}
}

bool
sge::console::gfx::object::active() const
{
	return
		active_;
}

void
sge::console::gfx::object::active(
	bool const _active
)
{
	active_ =
		_active;
}

bool
sge::console::gfx::object::input_active() const
{
	return
		input_active_;
}

void
sge::console::gfx::object::input_active(
	bool const _input_active
)
{
	input_active_ =
		_input_active;
}

void
sge::console::gfx::object::print(
	sge::font::string const &_string
)
{
	output_lines_.push_front(
		_string
	);
}

sge::console::object &
sge::console::gfx::object::console_object()
{
	return
		object_;
}

sge::console::object const &
sge::console::gfx::object::console_object() const
{
	return
		object_;
}

sge::console::gfx::sprite_object &
sge::console::gfx::object::background_sprite()
{
	return
		background_;
}

sge::console::gfx::sprite_object const &
sge::console::gfx::object::background_sprite() const
{
	return
		background_;
}

sge::font::unit
sge::console::gfx::object::render_line(
	sge::renderer::context::ffp &_render_context,
	sge::font::string const &_line,
	sge::font::unit const _current_y
)
{
	sge::font::draw::static_text static_text(
		renderer_,
		font_object_,
		_line,
		sge::font::text_parameters(
			sge::font::align_h::left(
				sge::font::align_h::max_width(
					background_.w()
				)
			)
		),
		sge::font::vector::null(),
		font_color_.get(),
		// FIXME
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::font::vector const pos(
		0,
		_current_y
		-
		static_text.rect().bottom()
	);;

	static_text.pos(
		pos
		+
		background_.pos()
	);

	static_text.draw(
		_render_context
	);

	return
		pos.y();
}

void
sge::console::gfx::object::key_callback(
	sge::input::keyboard::key_event const &_key
)
{
	if(
		active_
		&&
		_key.pressed()
	)
		this->key_action(
			sge::input::keyboard::key_repeat_event(
				_key.key_code()
			)
		);
}

void
sge::console::gfx::object::char_callback(
	sge::input::keyboard::char_event const &_event
)
{
	if(
		!active_
		||
		!input_active_
	)
		return;

	// is a printable character? then append to input
	if(
		std::isprint(
			_event.character(),
			std::locale()
		)
	)
	{
		input_line_.insert(
			_event.character()
		);

		return;
	}
}

void
sge::console::gfx::object::key_action(
	sge::input::keyboard::key_repeat_event const &_event
)
{
	if(
		!active_
	)
		return;

	if(
		!input_active_
	)
		switch(
			_event.key_code()
		)
		{
		case sge::input::keyboard::key_code::pageup:
		case sge::input::keyboard::key_code::pagedown:
			break;
		default:
			return;
		}

	switch(
		_event.key_code()
	)
	{
		case sge::input::keyboard::key_code::w:
			if(
				keyboard_.mod_state()
				&
				sge::input::keyboard::modifier::control
			)
				input_line_.erase_word();
		break;
		case sge::input::keyboard::key_code::delete_:
			input_line_.erase_char();
		break;
		case sge::input::keyboard::key_code::backspace:
			if (input_line_.at_start())
				return;
			input_line_.left();
			input_line_.erase_char();
		break;
		case sge::input::keyboard::key_code::tab:
			input_line_.complete_word(object_.functions());
		break;
		case sge::input::keyboard::key_code::pageup:
			if(
				keyboard_.mod_state()
				&
				sge::input::keyboard::modifier::shift
			)
				output_lines_.to_end();
			else
				output_lines_.up();
		break;
		case sge::input::keyboard::key_code::pagedown:
			if(
				keyboard_.mod_state()
				&
				sge::input::keyboard::modifier::shift
			)
				output_lines_.to_begin();
			else
				output_lines_.down();
		break;
		case sge::input::keyboard::key_code::up:
			if (input_history_.empty())
				return;
			input_line_.string(
				*current_input_);
			if (current_input_ != --input_history_.end())
				++current_input_;
		break;
		case sge::input::keyboard::key_code::down:
			if (current_input_ != input_history_.begin())
			{
				--current_input_;
				input_line_.string(
					*current_input_);
			}
		break;
		case sge::input::keyboard::key_code::left:
			input_line_.left();
		break;
		case sge::input::keyboard::key_code::right:
			input_line_.right();
		break;
		case sge::input::keyboard::key_code::home:
			input_line_.to_start();
		break;
		case sge::input::keyboard::key_code::end:
			input_line_.to_end();
		break;
		case sge::input::keyboard::key_code::return_:
			if (input_line_.empty())
				return;

			try
			{
				object_.eval(
					input_line_.string());
			}
			catch(
				sge::console::exception const &_error
			)
			{
				this->print(
					SGE_FONT_LIT("console error: ")
					+
					_error.console_string()
				);
			}

			// add executed command to each history (at the front)...
			input_history_.push_front(
				input_line_.string());

			current_input_ =
				input_history_.begin();

			// clear input line
			input_line_.string(
				SGE_FONT_LIT("")
			);
		break;
		// else we get a million warnings about unhandled enumeration values
		default: break;
	}
}

void
sge::console::gfx::object::error(
	sge::font::string const &_string
)
{
	this->print(
		SGE_FONT_LIT("command error: ")
		+
		_string
	);
}

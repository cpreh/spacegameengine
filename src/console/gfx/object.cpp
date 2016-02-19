/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/console/error_callback.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/object.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
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
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
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
	sge::input::focus::object &_focus,
	sge::font::rect const &_area,
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
	focus_(
		_focus
	),
	mod_state_tracker_(
		_focus
	),
	key_connection_(
		focus_.key_callback(
			sge::input::focus::key_callback{
				std::bind(
					&sge::console::gfx::object::key_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	key_repeat_connection_(
		focus_.key_repeat_callback(
			sge::input::focus::key_repeat_callback{
				std::bind(
					&sge::console::gfx::object::key_action,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	char_connection_(
		_focus.char_callback(
			sge::input::focus::char_callback{
				std::bind(
					&sge::console::gfx::object::char_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	error_conn_(
		object_.register_error_callback(
			sge::console::error_callback{
				std::bind(
					&sge::console::gfx::object::error,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	message_conn_(
		object_.register_message_callback(
			sge::console::message_callback{
				std::bind(
					&sge::console::gfx::object::print,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	area_(
		_area
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
		fcppt::cast::size<
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
	sge::font::unit current_y(
		area_.size().h()
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
		auto const &element
		:
		boost::make_iterator_range(
			output_lines_.point(),
			output_lines_.end()
		)
	)
	{
		current_y =
			this->render_line(
				_render_context,
				element,
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

void
sge::console::gfx::object::area(
	sge::font::rect const &_area
)
{
	area_ =
		_area;
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
			sge::font::align_h::variant{
				sge::font::align_h::left(
					sge::font::align_h::max_width(
						area_.size().w()
					)
				)
			}
		),
		fcppt::math::vector::null<
			sge::font::vector
		>(),
		font_color_.get(),
		sge::renderer::texture::emulate_srgb::no
	);

	// TODO: Make this easier
	sge::font::vector const pos(
		0,
		_current_y
		-
		static_text.rect().bottom()
	);;

	static_text.pos(
		pos
		+
		area_.pos()
	);

	static_text.draw(
		_render_context
	);

	return
		pos.y();
}

void
sge::console::gfx::object::key_callback(
	sge::input::focus::key_event const &_key
)
{
	if(
		active_
		&&
		_key.pressed()
	)
		this->key_action(
			sge::input::focus::key_repeat_event(
				_key.key()
			)
		);
}

void
sge::console::gfx::object::char_callback(
	sge::input::focus::char_event const &_event
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
	sge::input::focus::key_repeat_event const &_event
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
			_event.key().code()
		)
		{
		case sge::input::key::code::pageup:
		case sge::input::key::code::pagedown:
			break;
		default:
			return;
		}

	switch(
		_event.key().code()
	)
	{
		case sge::input::key::code::w:
			if(
				mod_state_tracker_.mod_state()
				&
				sge::input::key::modifier::control
			)
				input_line_.erase_word();
		break;
		case sge::input::key::code::delete_:
			input_line_.erase_char();
		break;
		case sge::input::key::code::backspace:
			if (input_line_.at_start())
				return;
			input_line_.left();
			input_line_.erase_char();
		break;
		case sge::input::key::code::tab:
			input_line_.complete_word(object_.functions());
		break;
		case sge::input::key::code::pageup:
			if(
				mod_state_tracker_.mod_state()
				&
				sge::input::key::modifier::shift
			)
				output_lines_.to_end();
			else
				output_lines_.up();
		break;
		case sge::input::key::code::pagedown:
			if(
				mod_state_tracker_.mod_state()
				&
				sge::input::key::modifier::shift
			)
				output_lines_.to_begin();
			else
				output_lines_.down();
		break;
		case sge::input::key::code::up:
			if (input_history_.empty())
				return;
			input_line_.string(
				*current_input_);
			if (current_input_ != --input_history_.end())
				++current_input_;
		break;
		case sge::input::key::code::down:
			if (current_input_ != input_history_.begin())
			{
				--current_input_;
				input_line_.string(
					*current_input_);
			}
		break;
		case sge::input::key::code::left:
			input_line_.left();
		break;
		case sge::input::key::code::right:
			input_line_.right();
		break;
		case sge::input::key::code::home:
			input_line_.to_start();
		break;
		case sge::input::key::code::end:
			input_line_.to_end();
		break;
		case sge::input::key::code::return_:
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

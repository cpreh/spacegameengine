/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/height.hpp>
#include <sge/font/text/line_width.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/part.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/src/console/next_or_last.hpp>
#include <fcppt/chrono/time_point.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <locale>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef
std::vector
<
	sge::font::text::string
>
line_sequence;

line_sequence const
wrap(
	sge::font::metrics &metrics,
	sge::font::text::string const &s,
	sge::font::dim const &max_dim)
{
	if (s.empty())
		return line_sequence();

	line_sequence lines;

	for (sge::font::text::string::const_iterator i = s.begin(); i != s.end();)
	{

		sge::font::text::part const tp =
			sge::font::text::line_width(
				metrics,
				i,
				s.end(),
				max_dim.w(),
				sge::font::text::flags::none);

		lines.push_back(
			sge::font::text::string(
				i,
				tp.end()));

		i =
			tp.next_begin();
	}

	return lines;
}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::console::gfx::gfx(
	sge::console::object &_object,
	renderer::device &_rend,
	image::color::any::object const &_font_color,
	font::metrics &_metrics,
	input::keyboard::device &_keyboard,
	sge::console::sprite_object const &_background,
	output_line_limit const _line_limit
)
:
	object_(
		_object
	),
	font_metrics_(
		_metrics
	),
	font_drawer_(
		_rend,
		_font_color
	),
	keyboard_(
		_keyboard
	),
	key_connection_(
		keyboard_.key_callback(
			std::tr1::bind(
				&gfx::key_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	key_repeat_connection_(
		keyboard_.key_repeat_callback(
			std::tr1::bind(
				&gfx::key_action,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	char_connection_(
		_keyboard.char_callback(
			std::tr1::bind(
				&gfx::char_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	error_conn_(
		object_.register_error_callback(
			std::tr1::bind(
				&gfx::error,
				this,
				std::tr1::placeholders::_1))),
	message_conn_(
		object_.register_message_callback(
			std::tr1::bind(
				&gfx::print,
				this,
				std::tr1::placeholders::_1))),
	sprite_buffers_(
		_rend,
		sge::sprite::buffers::option::dynamic
	),
	background_(
		_background),
	active_(
		false),
	input_line_(),
	input_history_(),
	current_input_(
		input_history_.begin()),
	output_lines_(
		_line_limit)
{
}
FCPPT_PP_POP_WARNING

sge::console::gfx::~gfx()
{
}

void
sge::console::gfx::render()
{
	sge::sprite::process::one(
		background_,
		sprite_buffers_.buffers()
	);

	output_line_sequence::size_type const line_count =
		background_.h() < font::text::height(font_metrics_)
		?
			0
		:
			static_cast<output_line_sequence::size_type>(
				background_.h()/
				font::text::height(
					font_metrics_));

	font::unit current_y =
		static_cast<font::unit>(
			background_.y()+background_.h()-2*font::text::height(font_metrics_));

	for(
		output_line_sequence::const_iterator
			i =
				output_lines_.point(),
			end =
				next_or_last(
					output_lines_.point(),
					output_lines_.end(),
					line_count);
		i != end;
		++i)
	{
		// draw history lines
		font::text::draw(
			font_metrics_,
			font_drawer_,
			*i,
			font::rect(
				font::pos(
					background_.x(),
					current_y),
				font::dim(
					background_.w(),
					background_.h() - font::text::height(font_metrics_))),
			font::text::align_h::left,
			font::text::align_v::top,
			font::text::flags::none);
		current_y -=
			font::text::height(
				font_metrics_);
	}

	font::text::string const il =
		input_line_.edited(
			// This used to be "bool cursor_active" which was controlled by
			// a timer, but due to the unneccessary timer depenceny, this
			// was removed
			true);

	font::text::draw(
		font_metrics_,
		font_drawer_,
		il,
		font::rect(
			font::pos(
				static_cast<font::unit>(
					background_.x()),
				static_cast<font::unit>(
					background_.y()+background_.h()-font::text::height(font_metrics_))),
			font::dim(
				static_cast<font::unit>(
					background_.w()),
				static_cast<font::unit>(
					font::text::height(font_metrics_)))),
		font::text::align_h::left,
		font::text::align_v::top,
		font::text::flags::none);
}

bool
sge::console::gfx::active() const
{
	return
		active_;
}

void
sge::console::gfx::active(
	bool const _active
)
{
	active_ =
		_active;
}

void
sge::console::gfx::print(
	font::text::string const &_s
)
{
	line_sequence const sequence(
		wrap(
			font_metrics_,
			_s,
			fcppt::math::dim::structure_cast<font::dim>(
				background_.size())));

	for(
		line_sequence::const_iterator it(
			sequence.begin()
		);
		it != sequence.end();
		++it
	)
		output_lines_.push_front(
			*it);
}

sge::console::object &
sge::console::gfx::object()
{
	return
		object_;
}

sge::console::object const &
sge::console::gfx::object() const
{
	return
		object_;
}

sge::console::sprite_object &
sge::console::gfx::background_sprite()
{
	return background_;
}

sge::console::sprite_object const &
sge::console::gfx::background_sprite() const
{
	return background_;
}

void
sge::console::gfx::key_callback(
	input::keyboard::key_event const &_key
)
{
	if (
		active_
		&&
		_key.pressed()
	)
		this->key_action(
			input::keyboard::key_repeat_event(
				_key.key_code()
			)
		);
}

void
sge::console::gfx::char_callback(
	input::keyboard::char_event const &_event
)
{
	if (!active_)
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
sge::console::gfx::key_action(
	input::keyboard::key_repeat_event const &_event
)
{
	if (!active_)
		return;

	switch (_event.key_code())
	{
		case input::keyboard::key_code::w:
			if(
				keyboard_.mod_state()
				& input::keyboard::modifier::ctrl
			)
				input_line_.erase_word();
		break;
		case input::keyboard::key_code::delete_:
			input_line_.erase_char();
		break;
		case input::keyboard::key_code::backspace:
			if (input_line_.at_start())
				return;
			input_line_.left();
			input_line_.erase_char();
		break;
		case input::keyboard::key_code::tab:
			input_line_.complete_word(object_.functions());
		break;
		case input::keyboard::key_code::pageup:
			output_lines_.up();
		break;
		case input::keyboard::key_code::pagedown:
			output_lines_.down();
		break;
		case input::keyboard::key_code::up:
			if (input_history_.empty())
				return;
			input_line_.string(
				*current_input_);
			if (current_input_ != --input_history_.end())
				++current_input_;
		break;
		case input::keyboard::key_code::down:
			if (current_input_ != input_history_.begin())
			{
				--current_input_;
				input_line_.string(
					*current_input_);
			}
		break;
		case input::keyboard::key_code::left:
			input_line_.left();
		break;
		case input::keyboard::key_code::right:
			input_line_.right();
		break;
		case input::keyboard::key_code::home:
			input_line_.to_start();
		break;
		case input::keyboard::key_code::end:
			input_line_.to_end();
		break;
		case input::keyboard::key_code::return_:
			if (input_line_.empty())
				return;

			try
			{
				object_.eval(
					input_line_.string());
			}
			catch (console::exception const &_error)
			{
				print(
					SGE_FONT_TEXT_LIT("console error: ")
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
				SGE_FONT_TEXT_LIT("")
			);
		break;
		// else we get a million warnings about unhandled enumeration values
		default: break;
	}
}

void
sge::console::gfx::error(
	font::text::string const &s)
{
	print(
		SGE_FONT_TEXT_LIT("command error: ")+
		s);
}

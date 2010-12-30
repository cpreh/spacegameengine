/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "next_or_last.hpp"
#include <sge/console/gfx.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/line_width.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/height.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/pos.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/time/second_f.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/render_one.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>
#include <locale>

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
	sge::font::metrics_ptr const metrics,
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

sge::console::gfx::gfx(
	sge::console::object &_object,
	renderer::device_ptr const _rend,
	image::color::any::object const &_font_color,
	font::metrics_ptr const _metrics,
	input::keyboard::device &_keyboard,
	sprite_object const &_background,
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
		fcppt::make_shared_ptr<
			font::text::drawer_3d
		>(
			_rend,
			_font_color
		)
	),
	input_modifier_filter_(
		_keyboard
	),
	ic_(
		input_modifier_filter_.register_callback(
			std::tr1::bind(
				&gfx::key_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	irc_(
		input_modifier_filter_.register_repeat_callback(
			std::tr1::bind(
				&gfx::key_action,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
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
	sprite_system_(
		_rend),
	background_(
		_background),
	active_(
		false),
	input_line_(),
	cursor_blink_(
		time::second_f(
			static_cast<time::funit>(
				0.5)
		)
	),
	cursor_active_(
		false),
	input_history_(),
	current_input_(
		input_history_.begin()),
	output_lines_(
		_line_limit)
{
}

sge::console::gfx::~gfx() {}

void
sge::console::gfx::draw()
{
	sprite::render_one(
		sprite_system_,
		background_
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
			font::pos(
				background_.x(),
				current_y),
			font::dim(
				background_.w(), 
				background_.h() - font::text::height(font_metrics_)),
			font::text::align_h::left,
			font::text::align_v::top,
			font::text::flags::none);
		current_y -= 
			font::text::height(
				font_metrics_);
	}

	font::text::string const il = 
		input_line_.edited(
			cursor_active_);

	font::text::draw(
		font_metrics_,
		font_drawer_,
		il,
		font::pos(
			static_cast<font::unit>(
				background_.x()),
			static_cast<font::unit>(
				background_.y()+background_.h()-font::text::height(font_metrics_))),
		font::dim(
			static_cast<font::unit>(
				background_.w()),
			static_cast<font::unit>(
				font::text::height(font_metrics_))),
		font::text::align_h::left,
		font::text::align_v::top,
		font::text::flags::none);

	if (cursor_blink_.update_b())
		cursor_active_ = !cursor_active_;
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
	BOOST_FOREACH(
		font::text::string const &l,
		wrap(
			font_metrics_,
			_s,
			fcppt::math::dim::structure_cast<font::dim>(
				background_.size())))
		output_lines_.push_front(
			l);
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

void
sge::console::gfx::key_callback(
	input::keyboard::key_event const &k,
	input::modifier::states const &s
)
{
	if (active_ && k.pressed())
		key_action(
			k.key(),
			s);
}

void
sge::console::gfx::key_action(
	input::keyboard::key const &k,
	input::modifier::states const &s
)
{
	if (!active_)
		return;
	
	if(
		(
			k.character() == SGE_FONT_TEXT_LIT('w')
			|| k.character() == SGE_FONT_TEXT_LIT('W')
		)
		&&
		(
			s[input::keyboard::key_code::lctrl]
			|| s[input::keyboard::key_code::rctrl]
		)
	)
	{
		input_line_.erase_word();
		return;
	}

	// is a printable character? then append to input
	if(std::isprint(k.character(),std::locale()))
	{
		input_line_.insert(k.character());
		return;
	}

	switch (k.code())
	{
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
			catch (console::exception const &e)
			{
				print(
					SGE_FONT_TEXT_LIT("console error: ")
					+
					e.console_string()
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

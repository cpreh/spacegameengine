/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/console/object.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/font/text_size.hpp>
#include <sge/font/pos.hpp>
#include <sge/time/second_f.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/exception.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>
#include <locale>

sge::console::gfx::gfx(
	sge::console::object &_object,
	renderer::device_ptr const _rend,
	image::color::any::object const &_font_color,
	font::metrics_ptr const _metrics,
	input::system_ptr const _input_system,
	sprite_object const &_background,
	output_line_limit const _line_limit
)
:
	object_(
		_object),
	font_(
		_metrics,
		fcppt::make_shared_ptr<
			font::drawer_3d
		>(
			_rend,
			_font_color
		)
	),
	input_system_(
		_input_system),
	input_modifier_filter_(
		input_system_),
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
		static_cast<output_line_sequence::size_type>(
			(background_.h()-font_.height())/
			font_.height() + 1);
	
	font::unit current_y = 
		static_cast<font::unit>(
			background_.y()+background_.h()-2*font_.height());
			
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
		font_.draw_text(
			*i,
			font::pos(
				background_.x(),
				current_y),
			font::dim(
				background_.w(), 
				background_.h() - font_.height()),
			font::align_h::left,
			font::align_v::top);
		current_y -= 
			font_.height();
	}

	fcppt::string const il = 
		input_line_.edited(
			cursor_active_);

	font_.draw_text(
		il,
		font::pos(
			static_cast<font::unit>(
				background_.x()),
			static_cast<font::unit>(
				background_.y()+background_.h()-font_.height())),
		font::dim(
			static_cast<font::unit>(
				background_.w()),
			static_cast<font::unit>(
				font_.height())));

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
sge::console::gfx::print_line(
	fcppt::string const &_s
)
{
	FCPPT_ASSERT(
		_s.find(FCPPT_TEXT('\n')) == fcppt::string::npos);
	output_lines_.push_front(
		_s);
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
	input::key_pair const &k,
	input::modifier::states const &s
)
{
	if (active_ && k.value())
		key_action(
			k.key(),
			s);
}

void
sge::console::gfx::key_action(
	input::key_type const &k,
	input::modifier::states const &s
)
{
	if (!active_)
		return;
	
	if ((k.char_code() == FCPPT_TEXT('w') || k.char_code() == FCPPT_TEXT('W'))
	    && (s[input::kc::key_lctrl] || s[input::kc::key_rctrl]))
	{
		input_line_.erase_word();
		return;
	}

	// is a printable character? then append to input
	if(std::isprint(k.char_code(),std::locale()))
	{
		input_line_.insert(k.char_code());
		return;
	}

	switch (k.code())
	{
		case input::kc::key_delete:
			input_line_.erase_char();
		break;
		case input::kc::key_backspace:
			if (input_line_.at_start())
				return;
			input_line_.left();
			input_line_.erase_char();
		break;
		case input::kc::key_tab:
			input_line_.complete_word(object_.variables(),object_.functions());
		break;
		case input::kc::key_pageup:
			output_lines_.up();
		break;
		case input::kc::key_pagedown:
			output_lines_.down();
		break;
		case input::kc::key_up:
			if (input_history_.empty())
				return;
			if (current_input_ != --input_history_.end())
				++current_input_;
			input_line_.string(
				*current_input_);
		break;
		case input::kc::key_down:
			if (current_input_ != input_history_.begin())
			{
				--current_input_;
				input_line_.string(
					*current_input_);
			}
		break;
		case input::kc::key_left:
			input_line_.left();
		break;
		case input::kc::key_right:
			input_line_.right();
		break;
		case input::kc::key_home:
			input_line_.to_start();
		break;
		case input::kc::key_end:
			input_line_.to_end();
		break;
		case input::kc::key_return:
			if (input_line_.empty())
				return;

			try
			{
				object_.eval(
					input_line_.string());
			}
			catch (exception const &e)
			{
				print_line(
					FCPPT_TEXT("console error: ")+
					e.string());
			}

			// add executed command to each history (at the front)...
			input_history_.push_front(
				input_line_.string());

			current_input_ = 
				input_history_.begin();

			// clear input line
			input_line_.string(
				FCPPT_TEXT(""));
		break;
		// else we get a million warnings about unhandled enumeration values
		default: break;
	}
}

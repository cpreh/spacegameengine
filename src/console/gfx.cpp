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
#include <boost/foreach.hpp>
#include <locale>

sge::console::gfx::gfx(
	sge::console::object &_object,
	renderer::device_ptr const _rend,
	image::color::any::object const &_font_color,
	font::metrics_ptr const _metrics,
	input::system_ptr const _is,
	sprite_object const &_bg
)
:
	object_(_object),
	fn(
		_metrics,
		fcppt::make_shared_ptr<
			font::drawer_3d
		>(
			_rend,
			_font_color
		)
	),
	is(_is),
	mf(_is),
	ic(
		mf.register_callback(
			std::tr1::bind(
				&gfx::key_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	irc(
		mf.register_repeat_callback(
			std::tr1::bind(
				&gfx::key_action,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	ss(_rend),
	bg(_bg),
	active_(false),
	input_line_(),
	cursor_blink_(
		time::second_f(
			static_cast<time::funit>(0.5)
		)
	),
	cursor_active_(false),
	input_history_(),
	output_history_()
{
}

sge::console::gfx::~gfx()
{}

void
sge::console::gfx::draw()
{
	sprite::render_one(
		ss,
		bg
	);

	font::unit current_y = static_cast<font::unit>(bg.y()+bg.h()-2*fn.height());
	BOOST_FOREACH(
		fcppt::string const s,
		output_history_.lines_inside(
			detail::history::rect(
				fcppt::math::vector::structure_cast<detail::history::point>(
					bg.pos()
				),
				detail::history::dim(
					static_cast<detail::history::unit>(bg.w()),
					static_cast<detail::history::unit>(bg.h()-fn.height())
				)
			),
			static_cast<detail::history::unit>(fn.height())
		)
	)
	{
		// draw history lines
		fn.draw_text(
			s,
			font::pos(bg.x(),current_y),
			font::dim(bg.w(), bg.h() - fn.height()),
			font::align_h::left,
			font::align_v::top);
		current_y -= fn.height();
	}

	fcppt::string const il = input_line_.edited(cursor_active_);

	fn.draw_text(
		il,
		font::pos(
			static_cast<font::unit>(bg.x()),
			static_cast<font::unit>(bg.y()+bg.h()-fn.height())),
		font::dim(
			static_cast<font::unit>(bg.w()),
			static_cast<font::unit>(fn.height())));

	if (cursor_blink_.update_b())
		cursor_active_ = !cursor_active_;
}

bool
sge::console::gfx::active() const
{
	return active_;
}

void
sge::console::gfx::active(
	bool const _active
)
{
	active_ = _active;
}

void
sge::console::gfx::print(
	fcppt::string const &s
)
{
	output_history_.push_front(s);
}

sge::console::object &
sge::console::gfx::object()
{
	return object_;
}

sge::console::object const &
sge::console::gfx::object() const
{
	return object_;
}

void
sge::console::gfx::key_callback(
	input::key_pair const &k,
	input::modifier::states const &s
)
{
	if (!active_)
		return;

	if (k.value())
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
		input_line_.right();
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
			output_history_.up();
		break;
		case input::kc::key_pagedown:
			output_history_.down();
		break;
		case input::kc::key_up:
			input_history_.up();
			input_line_.string(input_history_.current());
		break;
		case input::kc::key_down:
			input_history_.down();
			input_line_.string(input_history_.current());
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
				object_.eval(input_line_.string());
			}
			catch (exception const &e)
			{
				print(FCPPT_TEXT("console error: ")+e.string());
			}

			// add executed command to each history (at the front)...
			input_history_.push_front(input_line_.string());

			// clear input line
			input_line_.reset();
		break;
		// else we get a million warnings about unhandled enumeration values
		default: break;
	}
}

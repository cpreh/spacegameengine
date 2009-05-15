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
#include "../utility/unlimited_text_size.hpp"
#include <sge/gui/unit.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/timer/object.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/manager.hpp>
#include <sge/time/second_f.hpp>
#include <sge/math/almost_zero.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/font/metrics.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <locale>

namespace
{
sge::gui::logger mylogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("edit"),
	false);

sge::gui::logger mygraphlogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("edit"),
	false);
}

sge::gui::widgets::edit::edit(
	parent_data const &_parent,
	parameters _params,
	line_type const _type,
	dim const &_desired_size)
:
	base(
		_parent,
		_params
			.keyboard_focus(keyboard_focus::receive)
			.size_policy(
				sge::gui::size_policy(
					axis_policy::can_grow,
					axis_policy::none))),
	type(_type),
	desired_size_(_desired_size),
	cursor_visible_(false),
	text_buffer_(),
	scroll_pos_(point::null()),
	cursor(text_)
{
}

sge::string const sge::gui::widgets::edit::text() const
{
	return text_;
}

void sge::gui::widgets::edit::text(string const &n)
{
	text_ = n;
	parent_manager().dirty(
		*this,
		rect(point::null(),size()));
}

sge::gui::point const &sge::gui::widgets::edit::scroll_pos() const
{
	return scroll_pos_;
}

sge::gui::dim const sge::gui::widgets::edit::desired_size() const
{
	return desired_size_;
}

sge::gui::image &sge::gui::widgets::edit::text_buffer()
{
	return text_buffer_;
}

sge::gui::image const &sge::gui::widgets::edit::text_buffer() const
{
	return text_buffer_;
}

void sge::gui::widgets::edit::process(events::keyboard_enter const &)
{
	cursor_visible_ = true;
	timer_ = 
		parent_manager().register_timer(
			sge::time::second_f(static_cast<time::funit>(0.5)),
			boost::bind(&edit::blink_callback,this));
}

sge::gui::key_handling::type sge::gui::widgets::edit::process(events::key const &k)
{
	if (math::almost_zero(k.value().value()))
		return key_handling::process;
	
	if (type == single_line && k.value().key().code() == input::kc::key_return)
	{
		return_pressed();
		return key_handling::process;
	}
	
	// hand over to delegate
	cursor.key_callback(k.value());

	// dirty since something might have changed
	parent_manager().dirty(
		*this,
		rect(
			point::null(),
			size()));

	return key_handling::process;
}

void sge::gui::widgets::edit::process(events::mouse_click const &)
{
	parent_manager().request_keyboard_focus(*this);
}

void sge::gui::widgets::edit::process(events::keyboard_leave const &)
{
	cursor_visible_ = false;
	timer_.reset();
}

void sge::gui::widgets::edit::blink_callback()
{
	cursor_visible_ = !cursor_visible_;
	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("blinking cursor, visibility: ") << cursor_visible_);
	parent_manager().dirty(
		*this,
		rect(
			point::null(),
			size()));
}

void sge::gui::widgets::edit::resize(dim const &d) const
{
	dim const text_size = text_buffer_.size();

	if (text_size.w() > d.w() && text_size.h() > d.h())
	{
		SGE_LOG_DEBUG(mygraphlogger,log::_1 << SGE_TEXT("no resize needed"));
		return;
	}
	
	text_buffer_.resize(
		dim(
			text_size.w() >= d.w() ? text_size.w() : d.w(),
			text_size.h() >= d.h() ? text_size.h() : d.h()));
}

void sge::gui::widgets::edit::refresh() const
{
	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("redrawing text buffer"));

	string const ntext = text_+SGE_TEXT(' ');

	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("getting font size"));

	font_info const font = 
		parent_manager().skin().standard_font();
	
	dim const d = 
		utility::unlimited_text_size(
			font.metrics(),
			ntext);

	SGE_LOG_DEBUG(mygraphlogger,log::_1 << SGE_TEXT("resizing buffer"));
	
	// text larger than buffer? resize!
	resize(d);

	canvas::object c(text_buffer_);

	// TODO: use a transparent background here and blit it with alpha blending
	// enabled OR introduce widgets::edit::background_color
	SGE_LOG_DEBUG(mygraphlogger,log::_1 << SGE_TEXT("filling background"));

	c.draw_rect(
		c.area(),
		internal_color(0xff,0xff,0xff,0xff),
		canvas::rect_type::solid);
	
	if (ntext.empty())
		return;
	
	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("drawing text: ") << ntext);

	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("cursor position is: ") << cursor.pos());

	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("text buffer size is: ")
						<< text_buffer_.size());

	point p;
	c.draw_text(
		font,
		ntext,
		point::null(),
		text_buffer_.size(),
		font::align_h::left,
		font::align_v::top,
		font::flags::default_,
		cursor.pos(),
		&p);

	SGE_LOG_DEBUG(
		mygraphlogger,
		log::_1 << SGE_TEXT("text drawn"));

	if (cursor_visible_)
	{
		unit const cursor_line = static_cast<unit>(
			std::count(
				ntext.begin(),
				ntext.begin()+cursor.pos()+1,
				SGE_TEXT('\n')));

		SGE_LOG_DEBUG(
			mygraphlogger,
			log::_1 << SGE_TEXT("the cursor is on line ") << cursor_line
							<< SGE_TEXT("and stands on the character: '") << ntext[cursor.pos()] 
							<< SGE_TEXT("'")); 

		unit const 
			cursor_start = 
				static_cast<unit>(cursor_line*font.metrics()->line_height()),
			cursor_end = 
				std::min(c.area().h()-1,cursor_start + font.metrics()->line_height());
			//	static_cast<unit>(cursor_start+2);

		SGE_LOG_DEBUG(
			mygraphlogger,
			log::_1 << SGE_TEXT("drawing cursor at ") << cursor_start); 

		// draw cursor
		c.draw_line(
			point(p.x(),cursor_start),
			point(p.x(),cursor_end),
			internal_color(0x00,0x00,0x00,0xff));
	}

	if (p.x() > size().w())
	 	// FIXME: + 5 is a bit awkward
		scroll_pos_.x() = p.x() - size().w() + 5;
	else
		scroll_pos_.x() = static_cast<unit>(0);
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_GFX_HPP_INCLUDED
#define SGE_CONSOLE_GFX_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include "../renderer/device_fwd.hpp"
#include "../input/system_fwd.hpp"
#include "../signals/scoped_connection.hpp"
#include "../sprite/system.hpp"
#include "../sprite/object.hpp"
#include <sge/time/timer.hpp>
#include <sge/time/unit.hpp>
#include "../texture/part_fwd.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include "arg_list.hpp"
#include <boost/noncopyable.hpp>
#include <deque>
#include <cstddef>

namespace sge
{
namespace console
{
class gfx : public boost::noncopyable 
{
public:
	SGE_SYMBOL gfx(
		renderer::device_ptr,
		texture::const_part_ptr,
		font::object_ptr,
		input::system_ptr,
		sprite::point const &,
		sprite::dim const &);
	SGE_SYMBOL void key_callback(
		input::key_pair const &);
	SGE_SYMBOL void key_action(
		input::key_type const &);
	SGE_SYMBOL void draw();
	SGE_SYMBOL time::unit
	change_cursor_rate(
		time::unit);
	SGE_SYMBOL void toggle(); 
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void print(string const &);
	SGE_SYMBOL void clear(arg_list const &);
	SGE_SYMBOL void dump(arg_list const &);

private:
	void tabcomplete(string &);

	typedef std::deque<string> history_container;

	renderer::device_ptr const rend;
	font::object_ptr const fn;
	signals::scoped_connection ic,irc;
	sprite::system ss;
	sprite::object bg;
	bool active_;

	// input and history stuff
	time::timer cursor_timer;
	action_var<time::unit>::type cursor_rate;
	bool cursor_active;
	string::value_type cursor_char;
	string il;
	string::size_type cursor_pos;
	history_container history;
	history_container input_history;
	history_container::iterator history_pos;
	history_container::iterator input_history_pos;
	std::size_t history_size;
};

}
}

#endif

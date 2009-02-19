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

#include <sge/console/object_fwd.hpp>
#include <sge/console/detail/history.hpp>
#include <sge/console/detail/cursor.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/any_color.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/font.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/time/timer.hpp>
#include <sge/signals/connection.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <boost/noncopyable.hpp>
#include <deque>

namespace sge
{
namespace console
{
class gfx : public boost::noncopyable 
{
public:
	SGE_SYMBOL gfx(
		object &,
		renderer::device_ptr,
		renderer::any_color font_color,
		font::metrics_ptr,
		input::system_ptr,
		sprite::object const &);

	SGE_SYMBOL void draw();
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void active(bool);
private:
	object &object_;
	font::font fn;
	input::modifier::filter mf;
	signals::connection const ic,irc;
	sprite::system ss;
	sprite::object bg;
	bool active_;

	detail::cursor input_line_;
	time::timer cursor_blink_;
	bool cursor_active_;
	detail::history input_history_;
	detail::history output_history_;

	SGE_SYMBOL void key_callback(
		input::key_pair const &,
		input::modifier::states const &);

	SGE_SYMBOL void key_action(
		input::key_type const &,
		input::modifier::states const &);

	void tab_complete(string &);
};

}
}

#endif

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


#ifndef SGE_CONSOLE_GFX_HPP_INCLUDED
#define SGE_CONSOLE_GFX_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/console/detail/history.hpp>
#include <sge/console/detail/cursor.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/object.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/time/timer.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace console
{

class gfx
{
	SGE_NONCOPYABLE(gfx)
public:
	typedef sge::sprite::choices<
		int,
		float,
		sprite::no_color
	> sprite_choices;

	typedef boost::mpl::vector1<
		sprite::with_texture
	> sprite_elements;

	typedef sprite::system<
		sprite_choices,
		sprite_elements
	>::type sprite_system;

	typedef sprite::object<
		sprite_choices,
		sprite_elements
	> sprite_object;

	SGE_SYMBOL gfx(
		sge::console::object &,
		renderer::device_ptr,
		image::color::any::object const &font_color,
		font::metrics_ptr,
		input::system_ptr,
		sprite_object const &
	);

	SGE_SYMBOL ~gfx();

	SGE_SYMBOL void draw();
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void active(bool);
	SGE_SYMBOL void print(string const &);
	SGE_SYMBOL sge::console::object &object();
	SGE_SYMBOL sge::console::object const &object() const;
private:
	sge::console::object &object_;
	font::object fn;
	input::system_ptr const is;
	input::modifier::filter mf;
	sge::signal::scoped_connection const ic, irc;

	sprite_system ss;
	sprite_object bg;
	bool active_;

	detail::cursor input_line_;
	time::timer cursor_blink_;
	bool cursor_active_;
	detail::history input_history_;
	detail::history output_history_;

	void
	key_callback(
		input::key_pair const &,
		input::modifier::states const &
	);

	void
	key_action(
		input::key_type const &,
		input::modifier::states const &
	);

	void tab_complete(string &);
};

}
}

#endif

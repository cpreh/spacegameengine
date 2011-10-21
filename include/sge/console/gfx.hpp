/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/console/cursor.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_system.hpp>
#include <sge/console/symbol.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/string.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <sge/sprite/object_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{

class gfx
{
	FCPPT_NONCOPYABLE(
		gfx
	);
public:
	SGE_CONSOLE_SYMBOL gfx(
		sge::console::object &,
		renderer::device &,
		image::color::any::object const &font_color,
		font::metrics &,
		input::keyboard::device &,
		sprite_object const &,
		output_line_limit
	);

	/// If destructor doesn't exist: undefined reference to `sge::sprite::system_base ...
	SGE_CONSOLE_SYMBOL ~gfx();

	SGE_CONSOLE_SYMBOL void
	render();

	SGE_CONSOLE_SYMBOL bool
	active() const;

	SGE_CONSOLE_SYMBOL void
	active(
		bool
	);

	SGE_CONSOLE_SYMBOL void
	print(
		font::text::string const &
	);

	SGE_CONSOLE_SYMBOL sge::console::object &
	object();

	SGE_CONSOLE_SYMBOL sge::console::object const &
	object() const;

	SGE_CONSOLE_SYMBOL sprite_object &
	background_sprite();

	SGE_CONSOLE_SYMBOL sprite_object const &
	background_sprite() const;
private:
	typedef
	std::list<font::text::string>
	input_history_sequence;

	sge::console::object &object_;

	font::metrics &font_metrics_;

	font::text::drawer_3d font_drawer_;

	input::keyboard::device &keyboard_;

	fcppt::signal::scoped_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		error_conn_,
		message_conn_;

	sprite_system sprite_system_;
	sprite_object background_;
	bool active_;

	cursor input_line_;
	input_history_sequence input_history_;
	input_history_sequence::iterator current_input_;
	output_line_sequence output_lines_;

	void
	key_callback(
		input::keyboard::key_event const &
	);

	void
	char_callback(
		input::keyboard::char_event const &
	);

	void
	key_action(
		input::keyboard::key_repeat_event const &
	);

	void
	tab_complete(
		font::text::string &
	);

	void
	error(
		font::text::string const &
	);
};

}
}

#endif

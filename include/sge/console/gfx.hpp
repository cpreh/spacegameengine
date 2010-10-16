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


#ifndef SGE_CONSOLE_GFX_HPP_INCLUDED
#define SGE_CONSOLE_GFX_HPP_INCLUDED

#include <sge/console/output_line_limit.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/cursor.hpp>
#include <sge/console/sprite_system.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/drawer_ptr.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/input/keyboard/collector_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_fwd.hpp>
#include <sge/time/timer.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/external_system_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <list>

namespace sge
{
namespace console
{

class gfx
{
	FCPPT_NONCOPYABLE(gfx)
public:
	SGE_SYMBOL gfx(
		sge::console::object &,
		renderer::device_ptr,
		image::color::any::object const &font_color,
		font::metrics_ptr,
		input::keyboard::collector &,
		sprite_object const &,
		output_line_limit
	);

	/// If destructor doesn't exist: undefined reference to `sge::sprite::system_base ...
	SGE_SYMBOL ~gfx();

	SGE_SYMBOL void
	draw();

	SGE_SYMBOL bool
	active() const;
	
	SGE_SYMBOL void
	active(
		bool
	);

	SGE_SYMBOL void
	print(
		fcppt::string const &
	);

	SGE_SYMBOL sge::console::object &
	object();

	SGE_SYMBOL sge::console::object const &
	object() const;
private:
	typedef 
	std::list<fcppt::string>
	input_history_sequence;

	sge::console::object &object_;

	font::metrics_ptr const font_metrics_;

	font::drawer_ptr const font_drawer_;

	input::modifier::filter input_modifier_filter_;

	fcppt::signal::scoped_connection const
		ic_,
		irc_,
		error_conn_,
		message_conn_;

	sprite_system sprite_system_;
	sprite_object background_;
	bool active_;

	cursor input_line_;
	time::timer cursor_blink_;
	bool cursor_active_;
	input_history_sequence input_history_;
	input_history_sequence::iterator current_input_;
	output_line_sequence output_lines_;

	void
	key_callback(
		input::keyboard::key_event const &,
		input::modifier::states const &
	);

	void
	key_action(
		input::keyboard::key const &,
		input::modifier::states const &
	);

	void
	tab_complete(
		fcppt::string &
	);

	void
	error(
		fcppt::string const &
	);
};

}
}

#endif

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CONSOLE_GFX_OBJECT_HPP_INCLUDED
#define SGE_CONSOLE_GFX_OBJECT_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/cursor.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/output_line_limit_fwd.hpp>
#include <sge/console/gfx/detail/pointed_history.hpp>
#include <sge/console/gfx/detail/symbol.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/input/focus/char_event_fwd.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/key_repeat_event_fwd.hpp>
#include <sge/input/focus/mod_state_tracker.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
namespace gfx
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	object(
		sge::console::object &,
		sge::renderer::device::ffp &,
		sge::console::gfx::font_color const &,
		sge::font::object &,
		sge::input::focus::object &,
		sge::font::rect const &,
		sge::console::gfx::output_line_limit
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	~object();

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::ffp &
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	bool
	active() const;

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	void
	active(
		bool
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	bool
	input_active() const;

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	void
	input_active(
		bool
	);

	void
	print(
		sge::font::string const &
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	void
	area(
		sge::font::rect const &
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	sge::console::object &
	console_object();

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	sge::console::object const &
	console_object() const;
private:
	typedef
	std::list<
		sge::font::string
	>
	input_history_sequence;

	sge::console::object &object_;

	sge::renderer::device::ffp &renderer_;

	sge::console::gfx::font_color const font_color_;

	sge::font::object &font_object_;

	sge::input::focus::object &focus_;

	sge::input::focus::mod_state_tracker mod_state_tracker_;

	fcppt::signal::auto_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		error_conn_,
		message_conn_;

	sge::font::rect area_;

	bool active_;

	bool input_active_;

	sge::console::gfx::cursor input_line_;

	sge::console::gfx::object::input_history_sequence input_history_;

	sge::console::gfx::object::input_history_sequence::iterator current_input_;

	sge::console::gfx::detail::pointed_history output_lines_;

	sge::font::unit
	render_line(
		sge::renderer::context::ffp &,
		sge::font::string const &,
		sge::font::unit
	);

	void
	key_callback(
		sge::input::focus::key_event const &
	);

	void
	char_callback(
		sge::input::focus::char_event const &
	);

	void
	key_action(
		sge::input::focus::key_repeat_event const &
	);

	void
	tab_complete(
		sge::font::string &
	);

	void
	error(
		sge::font::string const &
	);
};

}
}
}

#endif

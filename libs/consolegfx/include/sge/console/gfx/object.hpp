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
#include <sge/console/gfx/input_active.hpp>
#include <sge/console/gfx/output_line_limit_fwd.hpp>
#include <sge/console/gfx/detail/pointed_history.hpp>
#include <sge/console/gfx/detail/symbol.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/input/focus/key_fwd.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/mod_state_tracker.hpp>
#include <sge/input/focus/event/base_fwd.hpp>
#include <sge/input/focus/event/char_fwd.hpp>
#include <sge/input/focus/event/key_fwd.hpp>
#include <sge/input/focus/event/key_repeat_fwd.hpp>
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
		sge::font::rect const &,
		sge::console::gfx::output_line_limit
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	~object();

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::ffp &,
		sge::console::gfx::input_active
	);

	SGE_CONSOLE_GFX_DETAIL_SYMBOL
	void
	focus_event(
		sge::input::focus::event::base const &
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

	sge::input::focus::mod_state_tracker mod_state_tracker_;

	fcppt::signal::auto_connection const error_connection_;

	fcppt::signal::auto_connection const message_connection_;

	sge::font::rect area_;

	sge::console::gfx::cursor input_line_;

	sge::console::gfx::object::input_history_sequence input_history_;

	sge::console::gfx::object::input_history_sequence::iterator current_input_;

	sge::console::gfx::detail::pointed_history output_lines_;

	void
	print(
		sge::font::string const &
	);

	sge::font::unit
	render_line(
		sge::renderer::context::ffp &,
		sge::font::string const &,
		sge::font::unit
	);

	void
	on_key(
		sge::input::focus::event::key const &
	);

	void
	on_char(
		sge::input::focus::event::char_ const &
	);

	void
	on_key_repeat(
		sge::input::focus::event::key_repeat const &
	);

	void
	key_action(
		sge::input::focus::shared_ptr const &,
		sge::input::focus::key const &
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

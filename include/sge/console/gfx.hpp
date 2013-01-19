/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/console/font_color.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/symbol.hpp>
#include <sge/console/detail/pointed_history.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
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
	SGE_CONSOLE_SYMBOL
	gfx(
		sge::console::object &,
		sge::renderer::device::ffp &,
		sge::console::font_color const &,
		sge::font::object &,
		sge::input::keyboard::device &,
		sge::console::sprite_object const &,
		sge::console::output_line_limit
	);

	SGE_CONSOLE_SYMBOL
	~gfx();

	SGE_CONSOLE_SYMBOL
	void
	render(
		sge::renderer::context::ffp &
	);

	SGE_CONSOLE_SYMBOL
	bool
	active() const;

	SGE_CONSOLE_SYMBOL
	void
	active(
		bool
	);

	SGE_CONSOLE_SYMBOL
	bool
	input_active() const;

	SGE_CONSOLE_SYMBOL
	void
	input_active(
		bool
	);

	void
	print(
		sge::font::string const &
	);

	SGE_CONSOLE_SYMBOL
	sge::console::object &
	object();

	SGE_CONSOLE_SYMBOL
	sge::console::object const &
	object() const;

	SGE_CONSOLE_SYMBOL
	sge::console::sprite_object &
	background_sprite();

	SGE_CONSOLE_SYMBOL
	sge::console::sprite_object const &
	background_sprite() const;
private:
	typedef
	std::list<
		sge::font::string
	>
	input_history_sequence;

	sge::console::object &object_;

	sge::renderer::device::ffp &renderer_;

	sge::console::font_color const font_color_;

	sge::font::object &font_object_;

	sge::input::keyboard::device &keyboard_;

	fcppt::signal::scoped_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		error_conn_,
		message_conn_;

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers;

	sprite_buffers sprite_buffers_;

	typedef sge::sprite::state::all_choices sprite_state_choices;

	typedef sge::sprite::state::object<
		sprite_state_choices
	> sprite_state;

	typedef sge::sprite::state::parameters<
		sprite_state_choices
	> sprite_state_parameters;

	sprite_state sprite_state_;

	sge::console::sprite_object background_;

	bool active_;

	bool input_active_;

	sge::console::cursor input_line_;

	sge::console::gfx::input_history_sequence input_history_;

	sge::console::gfx::input_history_sequence::iterator current_input_;

	sge::console::detail::pointed_history output_lines_;

	sge::font::unit
	render_line(
		sge::renderer::context::ffp &,
		sge::font::string const &,
		sge::font::unit
	);

	void
	key_callback(
		sge::input::keyboard::key_event const &
	);

	void
	char_callback(
		sge::input::keyboard::char_event const &
	);

	void
	key_action(
		sge::input::keyboard::key_repeat_event const &
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

#endif

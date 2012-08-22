/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/console/output_line_sequence.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/symbol.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
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
		sge::renderer::device &,
		sge::image::color::any::object const &font_color,
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
		sge::renderer::context::object &
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

	sge::renderer::device &renderer_;

	sge::image::color::any::object const font_color_;

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

	sge::console::sprite_object background_;

	bool active_;

	sge::console::cursor input_line_;

	sge::console::gfx::input_history_sequence input_history_;

	sge::console::gfx::input_history_sequence::iterator current_input_;

	sge::console::output_line_sequence output_lines_;

	sge::font::unit
	render_line(
		sge::renderer::context::object &,
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

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


#ifndef SGE_CEGUI_DEFAULT_KEYBOARD_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_KEYBOARD_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>

namespace sge
{
namespace cegui
{
class default_keyboard
{
FCPPT_NONCOPYABLE(
	default_keyboard);
public:
	SGE_CEGUI_SYMBOL explicit
	default_keyboard(
		syringe &,
		sge::input::keyboard::device &);
private:
	syringe &syringe_;
	fcppt::signal::scoped_connection
		key_callback_,
		key_repeat_callback_,
		char_callback_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);

	void
	key_repeat_callback(
		sge::input::keyboard::key_repeat_event const &);

	void
	char_callback(
		sge::input::keyboard::char_event const &);
};
}
}

#endif

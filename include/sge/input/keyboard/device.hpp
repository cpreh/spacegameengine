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


#ifndef SGE_INPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/mod_state_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace input
{
namespace keyboard
{

class SGE_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_INPUT_SYMBOL
	device();
public:
	SGE_INPUT_SYMBOL
	virtual ~device() = 0;

	virtual fcppt::signal::auto_connection
	char_callback(
		keyboard::char_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	key_callback(
		keyboard::key_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	key_repeat_callback(
		keyboard::key_repeat_callback const &
	) = 0;

	virtual keyboard::mod_state const
	mod_state() const = 0;
};

}
}
}

#endif

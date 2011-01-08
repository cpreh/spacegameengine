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


#ifndef SGE_DINPUT_KEYBOARD_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_HPP_INCLUDED

#include "device.hpp"
#include "device_parameters_fwd.hpp"
#include "di.hpp"
#include "key_converter_fwd.hpp"
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <sge/input/keyboard/key_repeat_function.hpp>
#include <sge/input/keyboard/mod_state.hpp>
#include <sge/time/timer.hpp>
#include <awl/backends/windows/window/instance_ptr.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/string.hpp>
#include <map>

namespace sge
{
namespace dinput
{

class keyboard
:
	public sge::input::keyboard::device,
	public dinput::device
{
	FCPPT_NONCOPYABLE(
		keyboard
	)
public:
	keyboard(
		dinput::device_parameters const &
		dinput::key_converter const &,
	);

	~keyboard();

	fcppt::signal::auto_connection
	key_callback(
		sge::input::keyboard::key_callback const &		
	);

	fcppt::signal::auto_connection
	key_repeat_callback(
		sge::input::keyboard::key_repeat_callback const &
	);

	sge::input::keyboard::mod_state const
	mod_state() const;

	void
	dispatch();
private:
	fcppt::char_type
	keycode_to_char(
		input::key_code key
	) const;

	static BOOL CALLBACK
	enum_keyboard_keys(
		LPCDIDEVICEOBJECTINSTANCE,
		LPVOID
	);

	sge::input::keyboard::mod_state modifiers_;

	dinput::key_converter const &conv_;

	HKL kblayout_;

	typedef fcppt::signal::object<
		sge::input::keyboard::key_function
	> key_signal;

	typedef fcppt::signal::object<
		sge::input::keyboard::key_repeat_function
	> key_repeat_signal;

	key_signal key_signal_;

	key_repeat_signal_ key_repeat_signal_;

	sge::time::timer repeat_time_;

	fcppt::optional<input::key_type> old_key_;

	typedef std::map<
		unsigned,
		input::keyboard::key_code::type
	> key_map;

	key_map keys_;
};

}
}

#endif

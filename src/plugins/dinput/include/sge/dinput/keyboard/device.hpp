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


#ifndef SGE_DINPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/state_array.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/keyboard/device_fwd.hpp>
#include <sge/dinput/keyboard/info.hpp>
#include <sge/dinput/keyboard/key_converter_fwd.hpp>
#include <sge/dinput/keyboard/repeat_duration.hpp>
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/char_type.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_repeat_function.hpp>
#include <sge/input/keyboard/mod_state.hpp>
#include <sge/timer/basic_decl.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/container/array_decl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>



namespace sge
{
namespace dinput
{
namespace keyboard
{

class device
:
	public sge::input::keyboard::device,
	public dinput::device::object
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		dinput::device::parameters const &,
		dinput::keyboard::key_converter const &
	);

	~device();
private:
	fcppt::signal::auto_connection
	key_callback(
		sge::input::keyboard::key_callback const &
	);

	fcppt::signal::auto_connection
	key_repeat_callback(
		sge::input::keyboard::key_repeat_callback const &
	);

	fcppt::signal::auto_connection
	char_callback(
		sge::input::keyboard::char_callback const &
	);

	sge::input::keyboard::mod_state const
	mod_state() const;

	void
	on_dispatch(
		DIDEVICEOBJECTDATA const &
	);

	sge::input::keyboard::char_type
	keycode_to_char(
		sge::input::keyboard::key_code::type
	) const;

	sge::dinput::keyboard::key_converter const &converter_;

	HKL kblayout_;

	typedef fcppt::signal::object<
		sge::input::keyboard::key_function
	> key_signal;

	typedef fcppt::signal::object<
		sge::input::keyboard::key_repeat_function
	> key_repeat_signal;

	typedef fcppt::signal::object<
		sge::input::keyboard::char_function
	> char_signal;

	key_signal key_signal_;

	key_repeat_signal key_repeat_signal_;

	char_signal char_signal_;

	typedef sge::timer::basic<
		sge::timer::clocks::standard
	> repeat_timer;

	repeat_timer repeat_time_;

	typedef fcppt::optional<
		sge::input::keyboard::key_code::type
	> optional_key_code;

	optional_key_code old_key_code_;

	sge::dinput::keyboard::info const info_;

	sge::dinput::state_array states_;
};

}
}
}

#endif

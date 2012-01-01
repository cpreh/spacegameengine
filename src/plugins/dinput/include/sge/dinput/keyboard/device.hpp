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

#include <sge/dinput/keyboard/device_fwd.hpp>
#include <sge/dinput/keyboard/key_converter_fwd.hpp>
#include <sge/dinput/keyboard/repeat_duration.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/state_array.hpp>
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
#include <fcppt/chrono/duration_decl.hpp>
#include <fcppt/chrono/time_point_decl.hpp>
#include <fcppt/container/array_decl.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


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
	dispatch();
private:
	sge::input::keyboard::char_type
	keycode_to_char(
		input::keyboard::key_code::type
	) const;

	static BOOL CALLBACK
	enum_keyboard_keys(
		LPCDIDEVICEOBJECTINSTANCE,
		LPVOID
	);

	dinput::keyboard::key_converter const &conv_;

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
		timer::clocks::standard
	> repeat_timer;

	repeat_timer repeat_time_;

	typedef fcppt::optional<
		input::keyboard::key_code::type
	> optional_key_code;

	optional_key_code old_key_code_;

	typedef std::map<
		DWORD,
		input::keyboard::key_code::type
	> key_map;

	key_map keys_;

	dinput::state_array states_;
};

}
}
}

#endif

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


#ifndef SGE_X11INPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/x11input/joypad/device_fwd.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/raw_event_fwd.hpp>
#include <sge/x11input/device/window_event_fwd.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_signal.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_signal.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_signal.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11input
{
namespace joypad
{

class device
:
	public sge::input::joypad::device,
	public sge::x11input::device::object
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit device(
		x11input::device::parameters const &
	);

	~device();
private:
	fcppt::signal::auto_connection
	absolute_axis_callback(
		input::joypad::absolute_axis_callback const &
	);

	fcppt::signal::auto_connection
	button_callback(
		input::joypad::button_callback const &
	);

	fcppt::signal::auto_connection
	relative_axis_callback(
		input::joypad::relative_axis_callback const &
	);

	input::joypad::info const &
	info() const;

	void
	on_motion(
		x11input::device::raw_event const &
	);

	void
	on_button_down(
		x11input::device::window_event const &
	);

	void
	on_button_up(
		x11input::device::window_event const &
	);

	void
	button_event(
		x11input::device::window_event const &,
		bool pressed
	);

	input::joypad::info const info_;

	fcppt::signal::connection_manager const connections_;

	sge::input::joypad::absolute_axis_signal absolute_axis_signal_;

	sge::input::joypad::button_signal button_signal_;

	sge::input::joypad::relative_axis_signal relative_axis_signal_;
};

}
}
}

#endif

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


#ifndef SGE_X11INPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_signal.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/window_event_fwd.hpp>
#include <sge/x11input/keyboard/device_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object.hpp>


namespace sge
{
namespace x11input
{
namespace keyboard
{

class device
:
	public sge::input::keyboard::device,
	public sge::x11input::device::object
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit
	device(
		sge::x11input::device::parameters const &
	);

	~device()
	override;
private:
	fcppt::signal::auto_connection
	key_callback(
		sge::input::keyboard::key_callback const &
	)
	override;

	void
	on_key_press(
		sge::x11input::device::window_event const &
	);

	void
	on_key_release(
		sge::x11input::device::window_event const &
	);

	sge::input::keyboard::key_signal key_signal_;

	awl::backends::x11::window::object const &window_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}
}

#endif

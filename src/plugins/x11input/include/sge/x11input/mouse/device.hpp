/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_DEVICE_HPP_INCLUDED

#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_signal.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_signal.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/raw_event_fwd.hpp>
#include <sge/x11input/device/valuator/accu_map.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <sge/x11input/device/window_event_fwd.hpp>
#include <sge/x11input/mouse/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object.hpp>


namespace sge
{
namespace x11input
{
namespace mouse
{

class device
:
	public sge::input::mouse::device,
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
	axis_callback(
		sge::input::mouse::axis_callback const &
	)
	override;

	fcppt::signal::auto_connection
	button_callback(
		sge::input::mouse::button_callback const &
	)
	override;

	sge::input::mouse::info const &
	info() const
	override;

	void
	on_motion(
		sge::x11input::device::raw_event const &
	);

	void
	process_valuator(
		sge::x11input::device::valuator::index,
		sge::x11input::device::valuator::value
	);

	void
	on_button_down(
		sge::x11input::device::window_event const &
	);

	void
	on_button_up(
		sge::x11input::device::window_event const &
	);

	void
	button_event(
		sge::x11input::device::window_event const &,
		bool pressed
	);

	sge::x11input::device::valuator::accu_map accus_;

	fcppt::signal::auto_connection_container const connections_;

	sge::input::mouse::info const info_;

	sge::input::mouse::axis_signal axis_signal_;

	sge::input::mouse::button_signal button_signal_;
};

}
}
}

#endif

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


#ifndef SGE_X11INPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_DEVICE_HPP_INCLUDED

#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/x11input/device/valuator/accu_map.hpp>
#include <sge/x11input/device/valuator/pair_fwd.hpp>
#include <sge/x11input/event/raw_demuxer_fwd.hpp>
#include <sge/x11input/event/window_demuxer_fwd.hpp>
#include <sge/x11input/mouse/device_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace mouse
{

class device
:
	public
		sge::input::mouse::device,
	public
		fcppt::enable_shared_from_this<
			sge::x11input::mouse::device
		 >
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		sge::window::object &,
		awl::backends::x11::window::base const &,
		XIDeviceInfo const &,
		sge::x11input::event::window_demuxer &,
		sge::x11input::event::raw_demuxer &
	);

	~device()
	override;
private:
	sge::window::object &
	window() const
	override;

	sge::input::mouse::info const &
	info() const
	override;

	awl::event::container
	on_event(
		XIDeviceEvent const &
	);

	awl::event::container
	on_raw_event(
		XIRawEvent const &
	);

	awl::event::container
	on_motion(
		XIRawEvent const &
	);

	awl::event::base_unique_ptr
	process_valuator(
		sge::x11input::device::valuator::pair
	);

	awl::event::optional_base_unique_ptr
	on_button_down(
		XIDeviceEvent const &
	);

	awl::event::optional_base_unique_ptr
	on_button_up(
		XIDeviceEvent const &
	);

	awl::event::optional_base_unique_ptr
	button_event(
		XIDeviceEvent const &,
		sge::input::mouse::button_pressed
	);

	sge::window::object &sge_window_;

	sge::x11input::device::valuator::accu_map accus_;

	sge::input::mouse::info const info_;

	fcppt::signal::auto_connection const event_connection_;

	fcppt::signal::auto_connection const raw_event_connection_;
};

}
}
}

#endif

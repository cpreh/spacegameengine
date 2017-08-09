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

#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/window_demuxer_fwd.hpp>
#include <sge/x11input/keyboard/device_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace keyboard
{

class device
:
	public
		sge::input::keyboard::device,
	public
		fcppt::enable_shared_from_this<
			sge::x11input::keyboard::device
		>
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		sge::window::object &,
		sge::x11input::device::id,
		awl::backends::x11::window::base const &,
		sge::x11input::event::window_demuxer &
	);

	~device()
	override;
private:
	sge::window::object &
	window() const
	override;

	awl::event::container
	on_event(
		XIDeviceEvent const &
	);

	awl::event::optional_base_unique_ptr
	on_key_press(
		XIDeviceEvent const &
	);

	awl::event::base_unique_ptr
	on_key_release(
		XIDeviceEvent const &
	);

	awl::event::base_unique_ptr
	make_key_event(
		XIDeviceEvent const &,
		sge::input::key::pressed
	);

	sge::window::object &sge_window_;

	awl::backends::x11::window::base const &window_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif

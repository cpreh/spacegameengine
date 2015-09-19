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


#ifndef SGE_DINPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_DEVICE_HPP_INCLUDED

#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/mouse/device_fwd.hpp>
#include <sge/dinput/mouse/info.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_signal.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_signal.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace mouse
{

class device
:
	public sge::input::mouse::device,
	public sge::dinput::device::object
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit
	device(
		sge::dinput::device::parameters const &
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
	on_dispatch(
		DIDEVICEOBJECTDATA const &
	)
	override;

	sge::dinput::mouse::info const info_;

	sge::input::mouse::axis_signal axis_signal_;

	sge::input::mouse::button_signal button_signal_;
};

}
}
}

#endif

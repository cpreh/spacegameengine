/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_DINPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/dinput/has_cursor.hpp>
#include <sge/dinput/has_focus.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/joypad/device_fwd.hpp>
#include <sge/dinput/joypad/info.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_signal.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_signal.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_signal.hpp>
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
namespace joypad
{

class device
:
	public sge::input::joypad::device,
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

	~device();
private:
	fcppt::signal::auto_connection
	absolute_axis_callback(
		sge::input::joypad::absolute_axis_callback const &
	);

	fcppt::signal::auto_connection
	button_callback(
		sge::input::joypad::button_callback const &
	);

	fcppt::signal::auto_connection
	relative_axis_callback(
		sge::input::joypad::relative_axis_callback const &
	);

	sge::input::joypad::info const &
	info() const;

	bool
	needs_acquire(
		sge::dinput::has_focus,
		sge::dinput::has_cursor
	) const;

	void
	on_dispatch(
		DIDEVICEOBJECTDATA const &
	);

	sge::dinput::joypad::info const info_;

	sge::input::joypad::absolute_axis_signal absolute_axis_signal_;

	sge::input::joypad::button_signal button_signal_;

	sge::input::joypad::relative_axis_signal relative_axis_signal_;
};

}
}
}

#endif

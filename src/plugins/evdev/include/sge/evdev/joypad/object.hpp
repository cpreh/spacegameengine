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


#ifndef SGE_EVDEV_JOYPAD_OBJECT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_OBJECT_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/object_fwd.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_signal.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_signal.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_signal.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{

class object
:
	public sge::input::joypad::device
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::evdev::device::fd_unique_ptr,
		sge::evdev::joypad::info const &
	);

	~object();
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

	typedef fcppt::scoped_ptr<
		sge::evdev::device::fd
	> fd_scoped_ptr;

	fd_scoped_ptr const fd_;

	sge::evdev::joypad::info const info_;

	sge::input::joypad::absolute_axis_signal absolute_axis_;

	sge::input::joypad::button_signal button_;

	sge::input::joypad::relative_axis_signal relative_axis_;
};

}
}
}

#endif

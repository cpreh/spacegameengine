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


#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/mouse/discover_event.hpp>
#include <sge/input/mouse/remove_event.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/cursor/object_ptr.hpp>
#include <sge/x11input/device/manager/config_impl.hpp>
#include <sge/x11input/joypad/device.hpp>
#include <sge/x11input/joypad/device_ptr.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/keyboard/device_ptr.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <sge/x11input/mouse/device_ptr.hpp>


template class
sge::x11input::device::manager::config<
	sge::x11input::cursor::object_ptr,
	sge::input::cursor::discover_event,
	sge::input::cursor::remove_event
>;

template class
sge::x11input::device::manager::config<
	sge::x11input::keyboard::device_ptr,
	sge::input::keyboard::discover_event,
	sge::input::keyboard::remove_event
>;

template class
sge::x11input::device::manager::config<
	sge::x11input::mouse::device_ptr,
	sge::input::mouse::discover_event,
	sge::input::mouse::remove_event
>;

template class
sge::x11input::device::manager::config<
	sge::x11input::joypad::device_ptr,
	sge::input::joypad::discover_event,
	sge::input::joypad::remove_event
>;

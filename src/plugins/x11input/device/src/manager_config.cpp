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


#include "../manager_config_impl.hpp"
#include "../../cursor/object.hpp"
#include "../../cursor/object_ptr.hpp"
#include "../../joypad/device.hpp"
#include "../../joypad/device_ptr.hpp"
#include "../../keyboard/device.hpp"
#include "../../keyboard/device_ptr.hpp"
#include "../../mouse/device.hpp"
#include "../../mouse/device_ptr.hpp"
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/joypad/device_ptr.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/mouse/device_ptr.hpp>

template class
sge::x11input::device::manager_config<
	sge::x11input::cursor::object_ptr,
	sge::input::cursor::object_ptr
>;

template class
sge::x11input::device::manager_config<
	sge::x11input::keyboard::device_ptr,
	sge::input::keyboard::device_ptr
>;

template class
sge::x11input::device::manager_config<
	sge::x11input::mouse::device_ptr,
	sge::input::mouse::device_ptr
>;

template class
sge::x11input::device::manager_config<
	sge::x11input::joypad::device_ptr,
	sge::input::joypad::device_ptr
>;

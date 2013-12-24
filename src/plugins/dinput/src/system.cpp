/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/dinput/system.hpp>
#include <sge/dinput/processor.hpp>
#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::dinput::system::system()
{
}

sge::dinput::system::~system()
{
}

sge::input::processor_unique_ptr
sge::dinput::system::create_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
{
	return
		sge::input::processor_unique_ptr(
			fcppt::make_unique_ptr<
				sge::dinput::processor
			>(
				_window,
				_window_system
			)
		);
}

sge::input::capabilities_field const
sge::dinput::system::capabilities() const
{
	return
		sge::input::capabilities_field{
			sge::input::capabilities::cursor,
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse,
			sge::input::capabilities::joypad
		};
}

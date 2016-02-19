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


#include <sge/evdev/processor.hpp>
#include <sge/evdev/system.hpp>
#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::evdev::system::system()
:
	sge::input::system()
{
}

sge::evdev::system::~system()
{
}

sge::input::processor_unique_ptr
sge::evdev::system::create_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::evdev::processor
			>(
				_window,
				_window_system
			)
		);
}

sge::input::capabilities_field
sge::evdev::system::capabilities() const
{
	return
		sge::input::capabilities_field{
			sge::input::capabilities::joypad
		};
}

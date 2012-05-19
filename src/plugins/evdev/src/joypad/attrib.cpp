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


#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/attrib.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/input/joypad/discover_signal.hpp>
#include <awl/backends/x11/system/event/processor_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::attrib(
	awl::backends::x11::system::event::processor &_system_processor,
	sge::evdev::joypad::map &_map,
	sge::input::joypad::discover_signal &_discover,
	boost::filesystem::path const &_path
)
{
	if(
		_map.find(
			_path
		)
		!=
		_map.end()
	)
		return;

	sge::evdev::joypad::add(
		_system_processor,
		_map,
		_discover,
		_path
	);
}

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


#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/sdlinput/mouse/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sge::sdlinput::mouse::device::device(
	sge::window::object &_window
)
:
	sge::input::mouse::device{},
	window_{
		_window
	},
	info_{
		// TODO: Can SDL provide any of this information?
		sge::input::mouse::axis_info_container{
			sge::input::mouse::axis_info_container::vector{}
		},
		sge::input::mouse::button_info_container{
			sge::input::mouse::button_info_container::vector{}
		},
		sge::input::info::name{
			fcppt::string{
				FCPPT_TEXT("SDL2 mouse")
			}
		}
	}
{
}

sge::sdlinput::mouse::device::~device()
{
}

sge::window::object &
sge::sdlinput::mouse::device::window() const
{
	return
		this->window_;
}

sge::input::mouse::info const &
sge::sdlinput::mouse::device::info() const
{
	return
		this->info_;
}

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


#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/attrib.hpp>
#include <sge/evdev/joypad/find_path.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


awl::event::optional_base_unique_ptr
sge::evdev::joypad::attrib(
	fcppt::log::object &_log,
	sge::window::object &_window,
	awl::backends::posix::processor &_processor,
	sge::evdev::joypad::map &_map,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::join(
			fcppt::optional::make_if(
				!sge::evdev::joypad::find_path(
					_map,
					_path
				).has_value(),
				[
					&_log,
					&_window,
					&_processor,
					&_map,
					&_path
				]{
					return
						sge::evdev::joypad::add(
							_log,
							_window,
							_processor,
							_map,
							_path
						);
				}
			)
		);
}

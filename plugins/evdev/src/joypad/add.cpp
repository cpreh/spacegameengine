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
#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/discover.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


awl::event::optional_base_unique_ptr
sge::evdev::joypad::add(
	fcppt::log::object &_log,
	sge::window::object &_window,
	awl::backends::posix::processor &_processor,
	sge::evdev::joypad::map &_map,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::map(
			sge::evdev::joypad::create(
				_log,
				_window,
				_processor,
				_path
			),
			[
				&_map
			](
				sge::evdev::joypad::shared_ptr const _ptr
			)
			{
				FCPPT_ASSERT_ERROR(
					_map.insert(
						std::make_pair(
							_ptr->posix_fd(),
							_ptr
						)
					).second
				);

				return
					fcppt::unique_ptr_to_base<
						awl::event::base
					>(
						fcppt::make_unique_ptr<
							sge::input::joypad::event::discover
						>(
							_ptr
						)
					);
			}
		);
}

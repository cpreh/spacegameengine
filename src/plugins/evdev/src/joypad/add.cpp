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


#include <sge/evdev/device/create_fd.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/discover_signal.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::add(
	sge::evdev::joypad::map &_map,
	sge::input::joypad::discover_signal &_signal,
	boost::filesystem::path const &_path
)
{
	sge::evdev::device::fd_unique_ptr fd(
		sge::evdev::device::create_fd(
			_path
		)
	);

	return;
/*
	if(
		!fd
	)
		return;

	sge::evdev::joypad::info const info_value(
		sge::evdev::joypad::make_info(
			*fd
		)
	);

	if(
		info_value.info_container().buttons().empty()
	)
		return;

	typedef std::pair<
		sge::evdev::joypad::map::iterator,
		bool
	> insert_return;

	insert_return const ret(
		fcppt::container::ptr::insert_unique_ptr_map(
			_map,
			_path,
			fcppt::make_unique_ptr<
				sge::evdev::joypad::object
			>(
				fcppt::move(
					fd
				),
				fcppt::cref(
					info_value
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ret.second
	);

	_signal(
		sge::input::joypad::discover_event(
			*ret.first->second
		)
	);
*/
}

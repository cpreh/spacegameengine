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


#include <sge/evdev/logger.hpp>
#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/device/name.hpp>
#include <sge/evdev/device/unique_id.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/optional_info.hpp>
#include <sge/evdev/joypad/absolute_axis/info_container.hpp>
#include <sge/evdev/joypad/absolute_axis/make_info_container.hpp>
#include <sge/evdev/joypad/button/info_container.hpp>
#include <sge/evdev/joypad/button/make_info_container.hpp>
#include <sge/evdev/joypad/relative_axis/info_container.hpp>
#include <sge/evdev/joypad/relative_axis/make_info_container.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/info.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


sge::evdev::joypad::optional_info const
sge::evdev::joypad::make_info(
	sge::evdev::device::fd const &_fd
)
try
{
	sge::evdev::joypad::absolute_axis::info_container const absolute_axis(
		sge::evdev::joypad::absolute_axis::make_info_container(
			_fd
		)
	);

	sge::evdev::joypad::button::info_container const buttons(
		sge::evdev::joypad::button::make_info_container(
			_fd
		)
	);

	sge::evdev::joypad::relative_axis::info_container const relative_axis(
		sge::evdev::joypad::relative_axis::make_info_container(
			_fd
		)
	);

	return
		sge::evdev::joypad::optional_info(
			sge::evdev::joypad::info(
				sge::input::joypad::info(
					absolute_axis.infos(),
					buttons.infos(),
					relative_axis.infos(),
					sge::evdev::device::name(
						_fd
					),
					sge::evdev::device::unique_id(
						_fd
					)
				),
				sge::evdev::joypad::event_map(
					absolute_axis.event_map(),
					buttons.event_map(),
					relative_axis.event_map()
				)
			)
		);
}
catch(
	sge::input::exception const &_exception
)
{
	FCPPT_LOG_ERROR(
		sge::evdev::logger(),
		fcppt::log::_
			<< _exception.string()
	);

	return
		sge::evdev::joypad::optional_info();
}

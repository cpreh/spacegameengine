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


#include <sge/dinput/di.hpp>
#include <sge/dinput/has_cursor.hpp>
#include <sge/dinput/has_focus.hpp>
#include <sge/dinput/is_down.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/device.hpp>
#include <sge/dinput/joypad/make_info.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::dinput::joypad::device::device(
	sge::dinput::device::parameters const &_parameters
)
:
	sge::input::joypad::device(),
	sge::dinput::device::object(
		_parameters,
		c_dfDIJoystick2
	),
	info_(
		sge::dinput::joypad::make_info(
			this->get(),
			_parameters.name(),
			_parameters.guid()
		)
	),
	absolute_axis_signal_(),
	button_signal_(),
	relative_axis_signal_()
{
}

FCPPT_PP_POP_WARNING

sge::dinput::joypad::device::~device()
{
}

fcppt::signal::auto_connection
sge::dinput::joypad::device::absolute_axis_callback(
	sge::input::joypad::absolute_axis_callback const &_callback
)
{
	return
		absolute_axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::joypad::device::button_callback(
	sge::input::joypad::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::joypad::device::relative_axis_callback(
	sge::input::joypad::relative_axis_callback const &_callback
)
{
	return
		relative_axis_signal_.connect(
			_callback
		);
}

sge::input::joypad::info const &
sge::dinput::joypad::device::info() const
{
	return
		info_.input_info();
}

bool
sge::dinput::joypad::device::needs_acquire(
	sge::dinput::has_focus,
	sge::dinput::has_cursor
) const
{
	return
		true;
}

void
sge::dinput::joypad::device::on_dispatch(
	DIDEVICEOBJECTDATA const &_data
)
{
	{
		sge::dinput::joypad::absolute_axis_map::const_iterator const it(
			info_.absolute_axis_map().find(
				_data.dwOfs
			)
		);

		if(
			it != info_.absolute_axis_map().end()
		)
		{
			absolute_axis_signal_(
				sge::input::joypad::absolute_axis_event(
					sge::input::joypad::absolute_axis(
						info_.input_info().absolute_axes()[
							it->second
						].code(),
						it->second
					),
					static_cast<
						sge::input::joypad::axis_value
					>(
						_data.dwData
					)
				)
			);

			return;
		}
	}

	{
		sge::dinput::joypad::button_map::const_iterator const it(
			info_.button_map().find(
				_data.dwOfs
			)
		);

		if(
			it != info_.button_map().end()
		)
		{
			button_signal_(
				sge::input::joypad::button_event(
					it->second,
					sge::dinput::is_down(
						_data.dwData
					)
				)
			);

			return;
		}
	}

	{
		sge::dinput::joypad::relative_axis_map::const_iterator const it(
			info_.relative_axis_map().find(
				_data.dwOfs
			)
		);

		if(
			it != info_.relative_axis_map().end()
		)
		{
			relative_axis_signal_(
				sge::input::joypad::relative_axis_event(
					sge::input::joypad::relative_axis(
						info_.input_info().relative_axes()[
							it->second
						].code(),
						it->second
					),
					static_cast<
						sge::input::joypad::axis_value
					>(
						_data.dwData
					)
				)
			);

			return;
		}
	}
}

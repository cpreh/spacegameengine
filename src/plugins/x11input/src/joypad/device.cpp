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


#include <sge/x11input/joypad/device.hpp>
#include <sge/x11input/joypad/absolute_axis.hpp>
#include <sge/x11input/joypad/axis_value.hpp>
#include <sge/x11input/joypad/button_id.hpp>
#include <sge/x11input/joypad/info.hpp>
#include <sge/x11input/joypad/make_valuator_infos.hpp>
#include <sge/x11input/joypad/relative_axis.hpp>
#include <sge/x11input/joypad/valuator_info.hpp>
#include <sge/x11input/joypad/valuator_info_vector.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/raw_demuxer.hpp>
#include <sge/x11input/device/raw_event.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/mask_is_set.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::joypad::device::device(
	x11input::device::parameters const &_param
)
:
	sge::input::joypad::device(),
	sge::x11input::device::object(
		_param.id()
	),
	info_(
		x11input::joypad::info(
			_param.window().display(),
			_param.info()
		)
	),
	valuator_infos_(
		x11input::joypad::make_valuator_infos(
			_param.info()
		)
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_param.raw_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_RawMotion
					),
					_param.id(),
					std::tr1::bind(
						&device::on_motion,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_ButtonPress
					),
					_param.id(),
					std::tr1::bind(
						&device::on_button_down,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_ButtonRelease
					),
					_param.id(),
					std::tr1::bind(
						&device::on_button_up,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	absolute_axis_signal_(),
	button_signal_(),
	relative_axis_signal_()
{
}

sge::x11input::joypad::device::~device()
{
}

fcppt::signal::auto_connection
sge::x11input::joypad::device::absolute_axis_callback(
	input::joypad::absolute_axis_callback const &_callback
)
{
	return
		absolute_axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::joypad::device::button_callback(
	input::joypad::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::joypad::device::relative_axis_callback(
	input::joypad::relative_axis_callback const &_callback
)
{
	return
		relative_axis_signal_.connect(
			_callback
		);
}

sge::input::joypad::info const &
sge::x11input::joypad::device::info() const
{
	return info_;
}

void
sge::x11input::joypad::device::on_motion(
	x11input::device::raw_event const &_event
)
{
	XIValuatorState const &valuators(
		_event.get().valuators
	);

	if(
		valuators.mask_len == 0
	)
		return;

	double const *valuator(
		valuators.values
	);

	for(
		int index = 0;
		index < valuators.mask_len * 8;
		++index, ++valuator
	)
	{
		if(
			!x11input::mask_is_set(
				valuators.mask,
				index
			)
		)
			continue;

		x11input::joypad::valuator_info_vector::size_type const valuator_index(
			static_cast<
				x11input::joypad::valuator_info_vector::size_type
			>(
				index
			)
		);

		FCPPT_ASSERT_ERROR(
			valuator_index
			< valuator_infos_.size()
		);

		x11input::joypad::valuator_info const &val_info(
			valuator_infos_[
				valuator_index
			]
		);

		input::joypad::axis_value const value(
			x11input::joypad::axis_value(
				*valuator
			)
		);

		if(
			val_info.absolute()
		)
			absolute_axis_signal_(
				input::joypad::absolute_axis_event(
					x11input::joypad::absolute_axis(
						val_info.id(),
						info_.absolute_axis()
					),
					value
				)
			);
		else
			relative_axis_signal_(
				input::joypad::relative_axis_event(
					x11input::joypad::relative_axis(
						val_info.id(),
						info_.relative_axis()
					),
					value
				)
			);
	}
}

void
sge::x11input::joypad::device::on_button_down(
	x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		true
	);
}

void
sge::x11input::joypad::device::on_button_up(
	x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		false
	);
}

void
sge::x11input::joypad::device::button_event(
	x11input::device::window_event const &_event,
	bool const _pressed
)
{
	button_signal_(
		input::joypad::button_event(
			x11input::joypad::button_id(
				_event
			),
			_pressed
		)
	);
}

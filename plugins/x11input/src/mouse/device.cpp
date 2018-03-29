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


#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/input/mouse/event/button.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/pair.hpp>
#include <sge/x11input/device/valuator/range.hpp>
#include <sge/x11input/event/device_function.hpp>
#include <sge/x11input/event/raw_demuxer.hpp>
#include <sge/x11input/event/raw_function.hpp>
#include <sge/x11input/event/select.hpp>
#include <sge/x11input/event/type_c.hpp>
#include <sge/x11input/event/window_demuxer.hpp>
#include <sge/x11input/mouse/axis.hpp>
#include <sge/x11input/mouse/axis_value.hpp>
#include <sge/x11input/mouse/axis_value_accu_pair.hpp>
#include <sge/x11input/mouse/button.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <sge/x11input/mouse/info.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <brigand/sequences/list.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::mouse::device::device(
	sge::window::object &_sge_window,
	awl::backends::x11::window::base const &_window,
	XIDeviceInfo const &_info,
	sge::x11input::event::window_demuxer &_window_demuxer,
	sge::x11input::event::raw_demuxer &_raw_demuxer
)
:
	sge::input::mouse::device{},
	fcppt::enable_shared_from_this<
		sge::x11input::mouse::device
	>{},
	sge_window_{
		_sge_window
	},
	accus_{},
	info_{
		sge::x11input::mouse::info(
			_window.display(),
			_info
		)
	},
	event_connection_{
		_window_demuxer.on_event(
			sge::x11input::device::id{
				_info.deviceid
			},
			sge::x11input::event::device_function{
				std::bind(
					&sge::x11input::mouse::device::on_event,
					this,
					std::placeholders::_1
				)
			}
		)
	},
	raw_event_connection_{
		_raw_demuxer.on_event(
			sge::x11input::device::id{
				_info.deviceid
			},
			sge::x11input::event::raw_function{
				std::bind(
					&sge::x11input::mouse::device::on_raw_event,
					this,
					std::placeholders::_1
				)
			}
		)
	}
{
	sge::x11input::device::id const id{
		_info.deviceid
	};

	sge::x11input::event::select<
		brigand::list<
			sge::x11input::event::type_c<
				XI_ButtonPress
			>,
			sge::x11input::event::type_c<
				XI_ButtonRelease
			>
		>
	>(
		_window_demuxer,
		id
	);

	sge::x11input::event::select<
		brigand::list<
			sge::x11input::event::type_c<
				XI_RawMotion
			>
		>
	>(
		_raw_demuxer,
		id
	);
}

sge::x11input::mouse::device::~device()
{
}

sge::window::object &
sge::x11input::mouse::device::window() const
{
	return
		sge_window_;
}

sge::input::mouse::info const &
sge::x11input::mouse::device::info() const
{
	return
		info_;
}

awl::event::container
sge::x11input::mouse::device::on_event(
	XIDeviceEvent const &_event
)
{
	switch(
		_event.evtype
	)
	{
	case XI_ButtonPress:
		return
			fcppt::optional::to_container<
				awl::event::container
			>(
				this->on_button_down(
					_event
				)
			);
	case XI_ButtonRelease:
		return
			fcppt::optional::to_container<
				awl::event::container
			>(
				this->on_button_up(
					_event
				)
			);
	}

	return
		awl::event::container{};
}

awl::event::container
sge::x11input::mouse::device::on_raw_event(
	XIRawEvent const &_event
)
{
	return
		_event.evtype
		==
		XI_RawMotion
		?
			this->on_motion(
				_event
			)
		:
			awl::event::container{}
		;
}

awl::event::container
sge::x11input::mouse::device::on_motion(
	XIRawEvent const &_event
)
{
	return
		fcppt::algorithm::map<
			awl::event::container
		>(
			sge::x11input::device::valuator::range(
				_event.valuators
			),
			[
				this
			](
				sge::x11input::device::valuator::pair const _valuator
			)
			{
				return
					this->process_valuator(
						_valuator
					);
			}
		);
}

awl::event::base_unique_ptr
sge::x11input::mouse::device::process_valuator(
	sge::x11input::device::valuator::pair const _valuator
)
{
	sge::x11input::device::valuator::accu &accu(
		fcppt::container::get_or_insert(
			accus_,
			_valuator.index(),
			[](
				sge::x11input::device::valuator::index
			){
				return
					sge::x11input::device::valuator::accu{
						0.
					};
			}
		)
	);

	sge::x11input::mouse::axis_value_accu_pair const result{
		sge::x11input::mouse::axis_value(
			accu,
			_valuator.value()
		)
	};

	accu =
		result.second;

	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::mouse::event::axis
			>(
				this->fcppt_shared_from_this(),
				sge::x11input::mouse::axis(
					_valuator.index(),
					info_.axes()
				),
				result.first
			)
		);
}

awl::event::optional_base_unique_ptr
sge::x11input::mouse::device::on_button_down(
	XIDeviceEvent const &_event
)
{
	return
		this->button_event(
			_event,
			sge::input::mouse::button_pressed{
				true
			}
		);
}

awl::event::optional_base_unique_ptr
sge::x11input::mouse::device::on_button_up(
	XIDeviceEvent const &_event
)
{
	return
		this->button_event(
			_event,
			sge::input::mouse::button_pressed{
				false
			}
		);
}

awl::event::optional_base_unique_ptr
sge::x11input::mouse::device::button_event(
	XIDeviceEvent const &_event,
	sge::input::mouse::button_pressed const _pressed
)
{
	return
		fcppt::optional::make_if(
			!(
				_event.flags
				&
				XIPointerEmulated
			),
			[
				this,
				&_event,
				_pressed
			]{
				return
					fcppt::unique_ptr_to_base<
						awl::event::base
					>(
						fcppt::make_unique_ptr<
							sge::input::mouse::event::button
						>(
							this->fcppt_shared_from_this(),
							sge::input::mouse::button(
								sge::x11input::mouse::button(
									_event,
									info_.buttons()
								)
							),
							_pressed
						)
					);
			}
		);
}

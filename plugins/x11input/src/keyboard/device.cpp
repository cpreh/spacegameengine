//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/device_function.hpp>
#include <sge/x11input/event/select.hpp>
#include <sge/x11input/event/type_c.hpp>
#include <sge/x11input/event/window_demuxer.hpp>
#include <sge/x11input/key/is_repeated.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/keyboard/key_from_event.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


sge::x11input::keyboard::device::device(
	sge::window::object &_sge_window,
	sge::x11input::device::id const _id,
	awl::backends::x11::window::base const &_window,
	sge::x11input::event::window_demuxer &_window_demuxer
)
:
	sge::input::keyboard::device{},
	fcppt::enable_shared_from_this<
		sge::x11input::keyboard::device
	>{},
	sge_window_{
		_sge_window
	},
	window_{
		_window
	},
	event_connection_{
		_window_demuxer.on_event(
			_id,
			sge::x11input::event::device_function{
				std::bind(
					&sge::x11input::keyboard::device::on_event,
					this,
					std::placeholders::_1
				)
			}
		)
	}
{
	sge::x11input::event::select<
		metal::list<
			sge::x11input::event::type_c<
				XI_KeyPress
			>,
			sge::x11input::event::type_c<
				XI_KeyRelease
			>
		>
	>(
		_window_demuxer,
		_id
	);
}

sge::x11input::keyboard::device::~device()
{
}

sge::window::object &
sge::x11input::keyboard::device::window() const
{
	return
		sge_window_;
}

awl::event::container
sge::x11input::keyboard::device::on_event(
	XIDeviceEvent const &_event
)
{
	switch(
		_event.evtype
	)
	{
	case XI_KeyPress:
		return
			fcppt::optional::to_container<
				awl::event::container
			>(
				this->on_key_press(
					_event
				)
			);
	case XI_KeyRelease:
		return
			fcppt::container::make<
				awl::event::container
			>(
				this->on_key_release(
					_event
				)
			);
	}

	return
		awl::event::container{};
}

awl::event::optional_base_unique_ptr
sge::x11input::keyboard::device::on_key_press(
	XIDeviceEvent const &_event
)
{
	return
		fcppt::optional::make_if(
			!sge::x11input::key::is_repeated(
				_event
			).get(),
			[
				this,
				&_event
			]{
				return
					this->make_key_event(
						_event,
						sge::input::key::pressed{
							true
						}
					);
			}
		);
}

awl::event::base_unique_ptr
sge::x11input::keyboard::device::on_key_release(
	XIDeviceEvent const &_event
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			this->make_key_event(
				_event,
				sge::input::key::pressed{
					false
				}
			)
		);
}

awl::event::base_unique_ptr
sge::x11input::keyboard::device::make_key_event(
	XIDeviceEvent const &_event,
	sge::input::key::pressed const _pressed
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::keyboard::event::key
			>(
				this->fcppt_shared_from_this(),
				sge::x11input::keyboard::key_from_event(
					window_.display(),
					_event
				),
				_pressed
			)
		);
}

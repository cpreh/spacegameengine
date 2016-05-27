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


#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <sge/wlinput/cursor/button_code.hpp>
#include <sge/wlinput/cursor/button_state.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <sge/wlinput/cursor/position.hpp>
#include <sge/wlinput/cursor/scroll_code.hpp>
#include <sge/wlinput/cursor/scroll_value.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <stdint.h>
#include <fcppt/config/external_end.hpp>


namespace
{

void
pointer_enter(
	void *const _data,
	wl_pointer *,
	uint32_t,
	wl_surface *const _surface,
	wl_fixed_t const _surface_x,
	wl_fixed_t const _surface_y
)
{
	sge::wlinput::cursor::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::cursor::data *
		>(
			_data
		)
	);

	if(
		data.window_.surface()
		==
		_surface
	)
	{
		data.position_ =
			sge::input::cursor::optional_position{
				sge::wlinput::cursor::position(
					_surface_x,
					_surface_y
				)
			};

		data.move_signal_(
			sge::input::cursor::move_event{
				data.position_
			}
		);
	}
}

void
pointer_leave(
	void *const _data,
	wl_pointer *,
	uint32_t,
	wl_surface *const _surface
)
{
	sge::wlinput::cursor::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::cursor::data *
		>(
			_data
		)
	);

	if(
		data.window_.surface()
		==
		_surface
	)
	{
		data.position_ =
			sge::input::cursor::optional_position{};

		data.move_signal_(
			sge::input::cursor::move_event{
				data.position_
			}
		);
	}
}

void
pointer_motion(
	void *const _data,
	wl_pointer *,
	uint32_t,
	wl_fixed_t const _surface_x,
	wl_fixed_t const _surface_y
)
{
	sge::wlinput::cursor::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::cursor::data *
		>(
			_data
		)
	);

	if(
		data.position_.has_value()
	)
	{
		data.position_ =
			sge::input::cursor::optional_position{
				sge::wlinput::cursor::position(
					_surface_x,
					_surface_y
				)
			};

		data.move_signal_(
			sge::input::cursor::move_event{
				data.position_
			}
		);
	}
}

void
pointer_button(
	void *const _data,
	wl_pointer *,
	uint32_t,
	uint32_t,
	uint32_t const _button,
	uint32_t const _state
)
{
	sge::wlinput::cursor::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::cursor::data *
		>(
			_data
		)
	);

	fcppt::optional::maybe_void(
		data.position_,
		[
			_button,
			_state,
			&data
		](
			sge::input::cursor::position const _position
		)
		{
			data.button_signal_(
				sge::input::cursor::button_event{
					sge::wlinput::cursor::button_code(
						_button
					),
					_position,
					sge::wlinput::cursor::button_state(
						_state
					)
				}
			);
		}
	);
}

void
pointer_axis(
	void *,
	wl_pointer *,
	uint32_t,
	uint32_t,
	wl_fixed_t
)
{
}

void
pointer_frame(
	void *,
	wl_pointer *
)
{
}

void
pointer_axis_source(
	void *,
	wl_pointer *,
	uint32_t
)
{
}

void
pointer_axis_stop(
	void *,
	wl_pointer *,
	uint32_t,
	uint32_t
)
{
}

void
pointer_axis_discrete(
	void *const _data,
	wl_pointer *,
	uint32_t const _axis,
	int32_t const _discrete
)
{
	sge::wlinput::cursor::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::cursor::data *
		>(
			_data
		)
	);

	if(
		data.position_.has_value()
	)
		data.scroll_signal_(
			sge::input::cursor::scroll_event{
				sge::wlinput::cursor::scroll_code(
					_axis
				),
				sge::wlinput::cursor::scroll_value(
					_discrete
				)
			}
		);
}

wl_pointer_listener const pointer_listener{
	pointer_enter,
	pointer_leave,
	pointer_motion,
	pointer_button,
	pointer_axis,
	pointer_frame,
	pointer_axis_source,
	pointer_axis_stop,
	pointer_axis_discrete
};

}

sge::wlinput::cursor::object::object(
	awl::backends::wayland::window::object const &_window,
	awl::backends::wayland::seat const &_seat
)
:
	sge::input::cursor::object(),
	impl_{
		_seat
	},
	data_{
		_window
	}
{
	::wl_pointer_add_listener(
		impl_.get(),
		&pointer_listener,
		&data_
	);
}

sge::wlinput::cursor::object::~object()
{
}

fcppt::signal::auto_connection
sge::wlinput::cursor::object::button_callback(
	sge::input::cursor::button_callback const &_callback
)
{
	return
		data_.button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::cursor::object::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		data_.move_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::cursor::object::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		data_.scroll_signal_.connect(
			_callback
		);
}

sge::input::cursor::optional_position
sge::wlinput::cursor::object::position() const
{
	return
		data_.position_;
}

void
sge::wlinput::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
	// TODO: We need a different API here because this is not implementable in wayland
}

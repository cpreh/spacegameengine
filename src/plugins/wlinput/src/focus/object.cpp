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


#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/keymap.hpp>
#include <sge/wlinput/focus/mmap.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <sge/wlinput/focus/optional_keymap.hpp>
#include <sge/wlinput/focus/optional_state.hpp>
#include <sge/wlinput/focus/scoped_fd.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <stdint.h>
#include <fcppt/config/external_end.hpp>


namespace
{

void
keyboard_keymap(
	void *const _data,
	wl_keyboard *,
	uint32_t const _format,
	int32_t const _fd,
	uint32_t const _size
)
{
	sge::wlinput::focus::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::focus::data *
		>(
			_data
		)
	);

	awl::backends::posix::fd const fd{
		_fd
	};

	sge::wlinput::focus::scoped_fd const scoped_fd{
		fd
	};

	auto const remove_xkb(
		[
			&data
		]{
			data.xkb_state_ =
				sge::wlinput::focus::optional_state();

			data.xkb_keymap_ =
				sge::wlinput::focus::optional_keymap();
		}
	);


	if(
		_format
		!=
		WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1
	)
	{
		remove_xkb();

		return;
	}

	try
	{
		sge::wlinput::focus::mmap const mapped{
			fd,
			_size
		};

		sge::wlinput::focus::keymap &xkb_keymap{
			fcppt::optional::assign(
				data.xkb_keymap_,
				sge::wlinput::focus::keymap{
					data.xkb_context_,
					mapped.string()
				}
			)
		};

		data.xkb_state_ =
			sge::wlinput::focus::optional_state{
				sge::wlinput::focus::state{
					xkb_keymap
				}
			};
	}
	catch(
		fcppt::exception const &_error
	)
	{
		remove_xkb();

		// TODO: Is this safe?
		throw;
	}
	catch(
		...
	)
	{
		remove_xkb();

		throw;
	}
}

void
keyboard_enter(
	void *const _data,
	wl_keyboard *,
	uint32_t,
	wl_surface *const _surface,
	wl_array *
)
{
	sge::wlinput::focus::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::focus::data *
		>(
			_data
		)
	);

	if(
		_surface
		==
		data.window_.surface()
	)
	{
		data.entered_ =
			true;

		data.in_signal_(
			sge::input::focus::in_event{}
		);
	}
}

void
keyboard_leave(
	void *const _data,
	wl_keyboard *,
	uint32_t,
	wl_surface *const _surface
)
{
	sge::wlinput::focus::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::focus::data *
		>(
			_data
		)
	);

	if(
		_surface
		==
		data.window_.surface()
	)
	{
		data.entered_ =
			false;

		data.out_signal_(
			sge::input::focus::out_event{}
		);
	}
}

void
keyboard_key(
	void *const _data,
	wl_keyboard *,
	uint32_t const _serial,
	uint32_t const _time,
	uint32_t const _key,
	uint32_t const _state
)
{
}

void
keyboard_modifiers(
	void *const _data,
	wl_keyboard *,
	uint32_t,
	uint32_t const _mods_depressed,
	uint32_t const _mods_latched,
	uint32_t const _mods_locked,
	uint32_t const _group
)
{
	sge::wlinput::focus::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::focus::data *
		>(
			_data
		)
	);

	fcppt::optional::maybe_void(
		data.xkb_state_,
		[
			_mods_depressed,
			_mods_latched,
			_mods_locked,
			_group
		](
			sge::wlinput::focus::state const &_state
		)
		{
			::xkb_state_update_mask(
				_state.get(),
				_mods_depressed,
				_mods_latched,
				_mods_locked,
				0,
				0,
				_group
			);
		}
	);
}

void
keyboard_repeat_info(
	void *const _data,
	wl_keyboard *,
	int32_t const _rate,
	int32_t const _delay
)
{
	// TODO: How do we get repeated keys?
}

wl_keyboard_listener const keyboard_listener{
	keyboard_keymap,
	keyboard_enter,
	keyboard_leave,
	keyboard_key,
	keyboard_modifiers,
	keyboard_repeat_info
};

}

sge::wlinput::focus::object::object(
	sge::wlinput::xkb_context const &_xkb_context,
	awl::backends::wayland::window::object const &_window,
	awl::backends::wayland::seat const &_seat
)
:
	sge::input::focus::object(),
	impl_{
		_seat
	},
	data_{
		_xkb_context,
		_window
	}
{
	::wl_keyboard_add_listener(
		impl_.get(),
		&keyboard_listener,
		&data_
	);
}

sge::wlinput::focus::object::~object()
{
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::char_callback(
	sge::input::focus::char_callback const &_callback
)
{
	return
		data_.char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::key_callback(
	sge::input::focus::key_callback const &_callback
)
{
	return
		data_.key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::key_repeat_callback(
	sge::input::focus::key_repeat_callback const &_callback
)
{
	return
		data_.key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::in_callback(
	sge::input::focus::in_callback const &_callback
)
{
	return
		data_.in_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::out_callback(
	sge::input::focus::out_callback const &_callback
)
{
	return
		data_.out_signal_.connect(
			_callback
		);
}

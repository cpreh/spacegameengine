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


#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event.hpp>
#include <sge/input/focus/char_type.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/optional_code.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/wlinput/logger.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/get_keysym.hpp>
#include <sge/wlinput/focus/get_utf8_string.hpp>
#include <sge/wlinput/focus/keymap.hpp>
#include <sge/wlinput/focus/key_pressed.hpp>
#include <sge/wlinput/focus/mmap.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <sge/wlinput/focus/optional_keymap.hpp>
#include <sge/wlinput/focus/optional_state.hpp>
#include <sge/wlinput/focus/scoped_fd.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <sge/wlinput/focus/translate_keysym.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <sge/wlinput/focus/wl_to_xkb_keycode.hpp>
#include <awl/backends/posix/callback.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/backends/posix/timer.hpp>
#include <awl/backends/posix/timer_delay.hpp>
#include <awl/backends/posix/timer_period.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <stdint.h>
#include <cstdint>
#include <wayland-client-protocol.h>
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
		FCPPT_LOG_ERROR(
			sge::wlinput::logger(),
			fcppt::log::_
				<<
				_error.string()
		);

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

		data.last_pressed_ =
			sge::input::key::optional_code();

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

		data.last_pressed_ =
			sge::input::key::optional_code();

		data.out_signal_(
			sge::input::focus::out_event{}
		);
	}
}

void
keyboard_key(
	void *const _data,
	wl_keyboard *,
	uint32_t,
	uint32_t,
	uint32_t const _key,
	uint32_t const _state
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
			&data,
			_key,
			_state
		](
			sge::wlinput::focus::state const &_xkb_state
		)
		{
			sge::wlinput::focus::xkb_keycode const xkb_keycode{
				sge::wlinput::focus::wl_to_xkb_keycode(
					_key
				)
			};

			sge::input::key::pressed const pressed{
				sge::wlinput::focus::key_pressed(
					_state
				)
			};

			sge::input::key::code const key_code{
				sge::wlinput::focus::translate_keysym(
					sge::wlinput::focus::get_keysym(
						_xkb_state,
						xkb_keycode
					)
				)
			};

			if(
				pressed.get()
			)
				data.last_pressed_ =
					sge::input::key::optional_code{
						key_code
					};
			else if(
				data.last_pressed_
				==
				sge::input::key::optional_code{
					key_code
				}
			)
				data.last_pressed_ =
					sge::input::key::optional_code{};

			data.key_signal_(
				sge::input::focus::key_event{
					sge::input::focus::key{
						key_code
					},
					pressed
				}
			);

			for(
				sge::input::focus::char_type const ch
				:
				sge::charconv::convert<
					sge::charconv::encoding::wchar,
					sge::charconv::encoding::utf8
				>(
					sge::wlinput::focus::get_utf8_string(
						_xkb_state,
						xkb_keycode
					)
				)
			)
				data.char_signal_(
					sge::input::focus::char_event{
						ch
					}
				);
		}
	);
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
	sge::wlinput::focus::data &data(
		*fcppt::cast::from_void_ptr<
			sge::wlinput::focus::data *
		>(
			_data
		)
	);

	auto const convert_duration(
		[](
			std::int32_t const _duration
		)
		{
			return
				awl::backends::posix::duration{
					_duration
				};
		}
	);

	data.repeat_timer_ =
		fcppt::optional::make(
			data.posix_processor_.create_timer(
				awl::backends::posix::callback{
					[
						&data
					](
						awl::backends::posix::event const &
					)
					{
						fcppt::optional::maybe_void(
							data.last_pressed_,
							[
								&data
							](
								sge::input::key::code const _code
							)
							{
								data.key_repeat_signal_(
									sge::input::focus::key_repeat_event{
										sge::input::focus::key{
											_code
										}
									}
								);
							}
						);
					}
				},
				awl::backends::posix::timer_delay{
					convert_duration(
						_delay
					)
				},
				awl::backends::posix::timer_period{
					convert_duration(
						_rate
					)
				}
			)
		);
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
	awl::backends::posix::processor &_posix_processor,
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
		_posix_processor,
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

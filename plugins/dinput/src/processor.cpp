//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/create_dinput.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/enum_devices.hpp>
#include <sge/dinput/has_focus.hpp>
#include <sge/dinput/processor.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/joypad/device.hpp>
#include <sge/dinput/keyboard/device.hpp>
#include <sge/dinput/mouse/device.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <awl/backends/windows/system/event/handle.hpp>
#include <awl/backends/windows/system/event/handle_matches.hpp>
#include <awl/backends/windows/system/event/processor.hpp>
#include <awl/backends/windows/window/has_focus.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/system/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::dinput::processor::processor(
	fcppt::log::object &_log,
	sge::window::object &_window
)
:
	sge::input::processor{},
	log_{
		_log
	},
	window_{
		_window
	},
	dinput_{
		sge::dinput::create_dinput()
	},
	windows_window_{
		fcppt::cast::dynamic_exn<
			awl::backends::windows::window::object &
		>(
			_window.awl_object()
		)
	},
	event_handle_{
		fcppt::cast::dynamic_exn<
			awl::backends::windows::system::event::processor &
		>(
			_window.system().awl_system().processor()
		).create_event_handle()
	},
	has_focus_{
		awl::backends::windows::window::has_focus(
			windows_window_
		)
	},
	keyboards_{},
	mice_{},
	joypads_{},
	event_connection_{
		_window.system().event_handler(
			sge::window::system_event_function{
				[
					this
				](
					awl::event::base const &_event
				)
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	},
	window_event_connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_window_event(
							_event
						);
				}
			}
		)
	}
{
	// TODO: How do we know if devices are added/removed?
	sge::dinput::enum_devices(
		*dinput_,
		enum_devices_callback,
		this
	);

	this->acquire_all();
}
FCPPT_PP_POP_WARNING

sge::dinput::processor::~processor()
{
}

sge::window::object &
sge::dinput::processor::window() const
{
	return
		window_;
}

sge::input::cursor::container
sge::dinput::processor::cursors() const
{
	return
		sge::input::cursor::container{};
}

sge::input::focus::container
sge::dinput::processor::foci() const
{
	return
		sge::input::focus::container{};
}

sge::input::joypad::container
sge::dinput::processor::joypads() const
{
	return
		fcppt::algorithm::map<
			sge::input::joypad::container
		>(
			joypads_,
			[](
				joypad_shared_ptr const &_joypad
			)
			->
			sge::input::joypad::shared_ptr
			{
				return
					_joypad;
			}
		);
}

sge::input::keyboard::container
sge::dinput::processor::keyboards() const
{
	return
		fcppt::algorithm::map<
			sge::input::keyboard::container
		>(
			keyboards_,
			[](
				keyboard_shared_ptr const &_keyboard
			)
			->
			sge::input::keyboard::shared_ptr
			{
				return
					_keyboard;
			}
		);
}

sge::input::mouse::container
sge::dinput::processor::mice() const
{
	return
		fcppt::algorithm::map<
			sge::input::mouse::container
		>(
			mice_,
			[](
				mouse_shared_ptr const &_mouse
			)
			->
			sge::input::mouse::shared_ptr
			{
				return
					_mouse;
			}
		);
}

template<
	typename State
>
State
sge::dinput::processor::fold_devices(
	State &&_state,
	fold_device_function<
		State
	> const &_function
)
{
	return
		fcppt::algorithm::fold(
			joypads_,
			fcppt::algorithm::fold(
				mice_,
				fcppt::algorithm::fold(
					keyboards_,
					std::move(
						_state
					),
					[
						&_function
					](
						keyboard_shared_ptr const &_keyboard,
						State &&_inner_state
					)
					{
						return
							_function(
								*_keyboard,
								std::move(
									_inner_state
								)
							);
					}
				),
				[
					&_function
				](
					mouse_shared_ptr const &_mouse,
					State &&_inner_state
				)
				{
					return
						_function(
							*_mouse,
							std::move(
								_inner_state
							)
						);
				}
			),
			[
				&_function
			](
				joypad_shared_ptr const &_joypad,
				State &&_inner_state
			)
			{
				return
					_function(
						*_joypad,
						std::move(
							_inner_state
						)
					);
			}
		);
}

void
sge::dinput::processor::for_each_device(
	for_each_device_function const &_function
)
{
	this->fold_devices(
		fcppt::unit{},
		fold_device_function<
			fcppt::unit
		>{
			[
				&_function
			](
				sge::dinput::device::object &_device,
				fcppt::unit
			)
			{
				_function(
					_device
				);

				return
					fcppt::unit{};
			}
		}
	);
}

void
sge::dinput::processor::acquire_all()
{
	this->for_each_device(
		for_each_device_function{
			[](
				sge::dinput::device::object &_device
			)
			{
				_device.acquire();
			}
		}
	);
}

void
sge::dinput::processor::on_focus_in()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("DirectInput: focus in")
	)

	has_focus_ =
		sge::dinput::has_focus(
			true
		);

	this->acquire_all();
}

void
sge::dinput::processor::on_focus_out()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("DirectInput: focus out")
	)

	has_focus_ =
		sge::dinput::has_focus(
			false
		);

	this->for_each_device(
		for_each_device_function{
			[](
				sge::dinput::device::object &_device
			)
			{
				_device.unacquire();
			}
		}
	);
}

awl::event::container
sge::dinput::processor::on_handle_ready()
{
	return
		this->fold_devices(
			awl::event::container{},
			fold_device_function<
				awl::event::container
			>{
				[](
					sge::dinput::device::object &_device,
					awl::event::container &&_state
				)
				{
					return
						fcppt::container::join(
							std::move(
								_state
							),
							_device.dispatch()
						);
				}
			}
		);
}

awl::event::container
sge::dinput::processor::on_event(
	awl::event::base const  &_event
)
{
	return
		awl::backends::windows::system::event::handle_matches(
			_event,
			*event_handle_
		)
		?
			this->on_handle_ready()
		:
			awl::event::container{}
		;
}

awl::event::container
sge::dinput::processor::on_window_event(
	awl::window::event::base const  &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			awl::backends::windows::window::event::generic const
		>(
			_event
		),
		[	
			this
		](
			fcppt::reference<
				awl::backends::windows::window::event::generic const
			> const _windows_event
		)
		{
			switch(
				_windows_event.get().type().get()
			)
			{
			case WM_SETFOCUS:
				this->on_focus_in();

				break;
			case WM_KILLFOCUS:
				this->on_focus_out();

				break;
			}
		}
	);

	return
		awl::event::container{};
}

BOOL
sge::dinput::processor::enum_devices_callback(
	LPCDIDEVICEINSTANCE const _ddi,
	LPVOID const _state
)
{
	sge::dinput::processor &instance(
		*fcppt::cast::from_void_ptr<
			sge::dinput::processor *
		>(
			_state
		)
	);

	DWORD const dev_type(
		_ddi->dwDevType
		& 0xFF
	);

	sge::input::info::name const name{
		fcppt::string{
			_ddi->tszProductName
		}
	};

	sge::dinput::device::parameters const parameters{
		*instance.dinput_,
		_ddi->guidInstance,
		instance.window_,
		instance.windows_window_,
		*instance.event_handle_
	};

	switch(
		dev_type
	)
	{
	case DI8DEVTYPE_KEYBOARD:
		instance.keyboards_.push_back(
			fcppt::make_shared_ptr<
				sge::dinput::keyboard::device
			>(
				parameters
			)
		);
		break;
	case DI8DEVTYPE_MOUSE:
		instance.mice_.push_back(
			fcppt::make_shared_ptr<
				sge::dinput::mouse::device
			>(
				parameters,
				name
			)
		);
		break;
	case DI8DEVTYPE_JOYSTICK:
		instance.joypads_.push_back(
			fcppt::make_shared_ptr<
				sge::dinput::joypad::device
			>(
				parameters,
				name
			)
		);
		break;
	}

	return
		DIENUM_CONTINUE;
}

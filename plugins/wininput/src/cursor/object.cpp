//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/event/scroll.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/wininput/cursor/exclusive_mode.hpp>
#include <sge/wininput/cursor/get_pos.hpp>
#include <sge/wininput/cursor/object.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/has_focus.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/screen_to_client.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::object::object(
	sge::window::object_ref const _window,
	awl::backends::windows::window::object &_windows_window
)
:
	sge::input::cursor::object{},
	fcppt::enable_shared_from_this<
		sge::wininput::cursor::object
	>{},
	window_{
		_window
	},
	windows_window_{
		_windows_window
	},
	mode_{
		sge::input::cursor::mode::normal
	},
	has_focus_{
		awl::backends::windows::window::has_focus(
			_windows_window
		)
	},
	exclusive_mode_{},
	event_connection_{
		this->window().event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::wininput::cursor::object::~object()
{
}

sge::input::cursor::optional_position
sge::wininput::cursor::object::position() const
{
	return
		fcppt::optional::map(
			fcppt::optional::bind(
				sge::wininput::cursor::get_pos(),
				[
					this
				](
					POINT const _cursor_pos
				)
				{
					return
						awl::backends::windows::window::screen_to_client(
							windows_window_,
							_cursor_pos
						);
				}
			),
			[](
				POINT const _transformed_pos
			)
			{
				return
					sge::input::cursor::position(
						fcppt::cast::size<
							sge::input::cursor::position_unit
						>(
							_transformed_pos.x
						),
						fcppt::cast::size<
							sge::input::cursor::position_unit
						>(
							_transformed_pos.y
						)
					);
			}
		);
}

void
sge::wininput::cursor::object::mode(
	sge::input::cursor::mode const _mode
)
{
	mode_ =
		_mode;

	if(
		mode_
		==
		sge::input::cursor::mode::normal
	)
		exclusive_mode_ =
			optional_exclusive_mode_unique_ptr();
	else if(
		has_focus_
	)
		this->make_grab();
}

sge::window::object &
sge::wininput::cursor::object::window() const
{
	return
		window_.get();
}

void
sge::wininput::cursor::object::focus_out()
{
	has_focus_ =
		false;

	exclusive_mode_ =
		optional_exclusive_mode_unique_ptr();
}

void
sge::wininput::cursor::object::focus_in()
{
	has_focus_ =
		true;

	if(
		mode_
		==
		sge::input::cursor::mode::exclusive
	)
		this->make_grab();
}

void
sge::wininput::cursor::object::make_grab()
{
	if(
		exclusive_mode_.has_value()
	)
		return;

	exclusive_mode_ =
		optional_exclusive_mode_unique_ptr(
			fcppt::make_unique_ptr<
				sge::wininput::cursor::exclusive_mode
			>(
				window_,
				windows_window_
			)
		);
}

awl::event::container
sge::wininput::cursor::object::on_event(
	awl::window::event::base const &_event
)
{
	return
		fcppt::optional::to_container<
			awl::event::container
		>(
			fcppt::optional::bind(
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
					> const _window_event
				)
				{
					return
						this->on_window_event(
							_window_event.get()
						);
				}
			)
		);
}

awl::event::optional_base_unique_ptr
sge::wininput::cursor::object::on_window_event(
	awl::backends::windows::window::event::generic const &_event
)
{
	switch(
		_event.type().get()
	)
	{
	case WM_MOUSEMOVE:
		return
			awl::event::optional_base_unique_ptr{
				this->on_move_event(
					_event
				)
			};
	case WM_LBUTTONDOWN:
		this->focus_in();

		return
			awl::event::optional_base_unique_ptr{
				this->on_button_event(
					_event,
					sge::input::cursor::button_code::left,
					sge::input::cursor::button_pressed{
						true
					}
				)
			};
	case WM_LBUTTONUP:
		return
			awl::event::optional_base_unique_ptr{
				this->on_button_event(
					_event,
					sge::input::cursor::button_code::left,
					sge::input::cursor::button_pressed{
						false
					}
				)
			};
	case WM_MBUTTONDOWN:
		return
			awl::event::optional_base_unique_ptr{
				this->on_button_event(
					_event,
					sge::input::cursor::button_code::middle,
					sge::input::cursor::button_pressed{
						true
					}
				)
			};
	case WM_MBUTTONUP:
		return
			awl::event::optional_base_unique_ptr{
				this->on_button_event(
					_event,
					sge::input::cursor::button_code::middle,
					sge::input::cursor::button_pressed{
						false
					}
				)
			};
	case WM_RBUTTONDOWN:
		return
			awl::event::optional_base_unique_ptr{
				this->on_button_event(
					_event,
					sge::input::cursor::button_code::right,
					sge::input::cursor::button_pressed{
						true
					}
				)
			};
	case WM_RBUTTONUP:
		return
			awl::event::optional_base_unique_ptr{
				this->on_button_event(
					_event,
					sge::input::cursor::button_code::right,
					sge::input::cursor::button_pressed{
						false
					}
				)
			};
	case WM_MOUSEWHEEL:
		return
			awl::event::optional_base_unique_ptr{
				this->on_scroll_event(
					_event,
					sge::input::cursor::scroll_code::vertical
				)
			};
			// TODO: Why is there no WM_MOUSEHWHEEL?
			/*
			this->make_scroll_connection(
				ret,
				WM_MOUSEHWHEEL,
				sge::input::cursor::scroll_code::horizontal
			);*/
	}

	return
		awl::event::optional_base_unique_ptr{};
}

awl::event::base_unique_ptr
sge::wininput::cursor::object::on_move_event(
	awl::backends::windows::window::event::generic const &_event
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::cursor::event::move
			>(
				sge::input::cursor::shared_ptr{
					this->fcppt_shared_from_this()
				},
				sge::input::cursor::optional_position{
					sge::input::cursor::position{
						LOWORD(
							_event.lparam().get()
						),
						HIWORD(
							_event.lparam().get()
						)
					}
				}
			)
		);
}

awl::event::base_unique_ptr
sge::wininput::cursor::object::on_button_event(
	awl::backends::windows::window::event::generic const &_event,
	sge::input::cursor::button_code const _code,
	sge::input::cursor::button_pressed const _down
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::cursor::event::button
			>(
				sge::input::cursor::shared_ptr{
					this->fcppt_shared_from_this()
				},
				_code,
				sge::input::cursor::position(
					LOWORD(
						_event.lparam().get()
					),
					HIWORD(
						_event.lparam().get()
					)
				),
				_down
			)
		);
}

awl::event::base_unique_ptr
sge::wininput::cursor::object::on_scroll_event(
	awl::backends::windows::window::event::generic const &_event,
	sge::input::cursor::scroll_code const _code
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::cursor::event::scroll
			>(
				sge::input::cursor::shared_ptr{
					this->fcppt_shared_from_this()
				},
				_code,
				// TODO: How do we want to scale this?
				GET_WHEEL_DELTA_WPARAM(
					_event.wparam().get()
				)
			)
		);
}

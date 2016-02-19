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


#include <sge/wininput/has_focus.hpp>
#include <sge/wininput/cursor/exclusive_mode.hpp>
#include <sge/wininput/cursor/get_pos.hpp>
#include <sge/wininput/cursor/object.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_event.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/screen_to_client.hpp>
#include <awl/backends/windows/window/event/callback.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::object::object(
	awl::backends::windows::window::event::processor &_event_processor,
	awl::backends::windows::window::object &_window,
	sge::wininput::has_focus const _has_focus
)
:
	event_processor_(
		_event_processor
	),
	window_(
		_window
	),
	button_signal_(),
	move_signal_(),
	scroll_signal_(),
	mode_(
		sge::input::cursor::mode::normal
	),
	has_focus_(
		_has_focus
	),
	exclusive_mode_(),
	connections_(
		fcppt::algorithm::join(
			fcppt::assign::make_container<
				fcppt::signal::auto_connection_container
			>(
				event_processor_.register_callback(
					fcppt::strong_typedef_construct_cast<
						awl::backends::windows::event::type,
						fcppt::cast::to_unsigned_fun
					>(
						WM_MOUSEMOVE
					),
					awl::backends::windows::window::event::callback{
						std::bind(
							&sge::wininput::cursor::object::on_move,
							this,
							std::placeholders::_1
						)
					}
				)
			).move_container(),
			this->make_button_connections(
				WM_LBUTTONDOWN,
				WM_LBUTTONUP,
				sge::input::cursor::button_code::left
			),
			this->make_button_connections(
				WM_MBUTTONDOWN,
				WM_MBUTTONUP,
				sge::input::cursor::button_code::middle
			),
			this->make_button_connections(
				WM_RBUTTONDOWN,
				WM_RBUTTONUP,
				sge::input::cursor::button_code::right
			),
			fcppt::assign::make_container<
				fcppt::signal::auto_connection_container
			>(
				this->make_scroll_connection(
					WM_MOUSEWHEEL,
					sge::input::cursor::scroll_code::vertical
				)
			).move_container()
			// FIXME: Why is there no WM_MOUSEHWHEEL?
			/*
			this->make_scroll_connection(
				ret,
				WM_MOUSEHWHEEL,
				sge::input::cursor::scroll_code::horizontal
			);*/
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::wininput::cursor::object::~object()
{
}

fcppt::signal::auto_connection
sge::wininput::cursor::object::button_callback(
	sge::input::cursor::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wininput::cursor::object::move_callback(
	sge::input::cursor::move_callback const &_callback
)
{
	return
		move_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wininput::cursor::object::scroll_callback(
	sge::input::cursor::scroll_callback const &_callback
)
{
	return
		scroll_signal_.connect(
			_callback
		);
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
							window_,
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
		has_focus_.get()
	)
		this->make_grab();
}

void
sge::wininput::cursor::object::focus_out()
{
	has_focus_ =
		sge::wininput::has_focus{
			false
		};

	exclusive_mode_ =
		optional_exclusive_mode_unique_ptr();
}

void
sge::wininput::cursor::object::focus_in()
{
	has_focus_ =
		sge::wininput::has_focus{
			true
		};

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
				event_processor_,
				window_
			)
		);
}

awl::backends::windows::window::event::return_type
sge::wininput::cursor::object::on_move(
	awl::backends::windows::window::event::object const &_event
)
{
	move_signal_(
		sge::input::cursor::move_event(
			sge::input::cursor::optional_position(
				sge::input::cursor::position(
					LOWORD(
						_event.lparam().get()
					),
					HIWORD(
						_event.lparam().get()
					)
				)
			)
		)
	);

	return
		awl::backends::windows::window::event::return_type();
}

awl::backends::windows::window::event::return_type
sge::wininput::cursor::object::on_button(
	awl::backends::windows::window::event::object const &_event,
	sge::input::cursor::button_code const _code,
	sge::input::cursor::button_pressed const _down
)
{
	if(
		_code
		==
		sge::input::cursor::button_code::left
		&&
		_down.get()
	)
		this->focus_in();

	button_signal_(
		sge::input::cursor::button_event(
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

	return
		awl::backends::windows::window::event::return_type();
}

awl::backends::windows::window::event::return_type
sge::wininput::cursor::object::on_scroll(
	awl::backends::windows::window::event::object const &_event,
	sge::input::cursor::scroll_code const _code
)
{
	// TODO: How do we want to scale this?

	scroll_signal_(
		sge::input::cursor::scroll_event(
			_code,
			GET_WHEEL_DELTA_WPARAM(
				_event.wparam().get()
			)
		)
	);

	return
		awl::backends::windows::window::event::return_type();
}

fcppt::signal::auto_connection_container
sge::wininput::cursor::object::make_button_connections(
	awl::backends::windows::event::type::value_type const _down_event,
	awl::backends::windows::event::type::value_type const _up_event,
	sge::input::cursor::button_code const _code
)
{
	return
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			event_processor_.register_callback(
				awl::backends::windows::event::type{
					_down_event
				},
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::cursor::object::on_button,
						this,
						std::placeholders::_1,
						_code,
						sge::input::cursor::button_pressed{
							true
						}
					)
				}
			)
		)(
			event_processor_.register_callback(
				awl::backends::windows::event::type{
					_up_event
				},
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::cursor::object::on_button,
						this,
						std::placeholders::_1,
						_code,
						sge::input::cursor::button_pressed{
							false
						}
					)
				}
			)
		);
}

fcppt::signal::auto_connection
sge::wininput::cursor::object::make_scroll_connection(
	awl::backends::windows::event::type::value_type const _event,
	sge::input::cursor::scroll_code const _code
)
{
	return
		event_processor_.register_callback(
			awl::backends::windows::event::type{
				_event
			},
			awl::backends::windows::window::event::callback{
				std::bind(
					&sge::wininput::cursor::object::on_scroll,
					this,
					std::placeholders::_1,
					_code
				)
			}
		);
}

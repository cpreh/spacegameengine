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
#include <sge/input/focus/char_event.hpp>
#include <sge/input/focus/char_type.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/key_repeat_event.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/wininput/focus/object.hpp>
#include <sge/wininput/focus/translate_key_code.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/event/callback.hpp>
#include <awl/backends/windows/window/event/object.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assign/make_container.hpp>
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

sge::wininput::focus::object::object(
	awl::backends::windows::window::event::processor &_event_processor
)
:
	event_processor_(
		_event_processor
	),
	char_signal_(),
	key_signal_(),
	key_repeat_signal_(),
	in_signal_(),
	out_signal_(),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_CHAR
				),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::focus::object::on_char,
						this,
						std::placeholders::_1
					)
				}
			),
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_KEYDOWN
				),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::focus::object::on_key,
						this,
						std::placeholders::_1,
						sge::input::key::pressed{
							true
						}
					)
				}
			),
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_KEYUP
				),
				awl::backends::windows::window::event::callback{
					std::bind(
						&sge::wininput::focus::object::on_key,
						this,
						std::placeholders::_1,
						sge::input::key::pressed{
							false
						}
					)
				}
			),
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_SETFOCUS
				),
				awl::backends::windows::window::event::callback{
					[
						this
					](
						awl::backends::windows::window::event::object const &
					)
					{
						in_signal_(
							sge::input::focus::in_event{}
						);

						return
							awl::backends::windows::window::event::return_type();
					}
				}
			),
			event_processor_.register_callback(
				fcppt::strong_typedef_construct_cast<
					awl::backends::windows::event::type,
					fcppt::cast::to_unsigned_fun
				>(
					WM_KILLFOCUS
				),
				awl::backends::windows::window::event::callback{
					[
						this
					](
						awl::backends::windows::window::event::object const &
					)
					{
						out_signal_(
							sge::input::focus::out_event{}
						);

						return
							awl::backends::windows::window::event::return_type();
					}
				}
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::wininput::focus::object::~object()
{
}

fcppt::signal::auto_connection
sge::wininput::focus::object::char_callback(
	sge::input::focus::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wininput::focus::object::key_callback(
	sge::input::focus::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wininput::focus::object::key_repeat_callback(
	sge::input::focus::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wininput::focus::object::in_callback(
	sge::input::focus::in_callback const &_callback
)
{
	return
		in_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wininput::focus::object::out_callback(
	sge::input::focus::out_callback const &_callback
)
{
	return
		out_signal_.connect(
			_callback
		);
}

awl::backends::windows::window::event::return_type
sge::wininput::focus::object::on_char(
	awl::backends::windows::window::event::object const &_event
)
{
	char_signal_(
		sge::input::focus::char_event(
			static_cast<
				sge::input::focus::char_type
			>(
				_event.wparam().get()
			)
		)
	);

	return
		awl::backends::windows::window::event::return_type(
			0
		);
}

awl::backends::windows::window::event::return_type
sge::wininput::focus::object::on_key(
	awl::backends::windows::window::event::object const &_event,
	sge::input::key::pressed const _pressed
)
{
	sge::input::focus::key const key(
		sge::wininput::focus::translate_key_code(
			_event.wparam()
		)
	);

	if(
		_pressed.get()
		&&
		(
			// TODO: Make a function for this
			_event.lparam().get()
			&
			(
				fcppt::literal<
					LPARAM
				>(
					1
				)
				<<
				30u
			)
		)
		!=
		0
	)
		key_repeat_signal_(
			sge::input::focus::key_repeat_event(
				key
			)
		);
	else
		key_signal_(
			sge::input::focus::key_event(
				key,
				_pressed
			)
		);

	return
		awl::backends::windows::window::event::return_type(
			0
		);
}

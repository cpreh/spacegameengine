/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/capabilities_to_string.hpp>
#include <sge/input/create_multi_system.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/system.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/log/option_container.hpp>
#include <sge/src/systems/logger.hpp>
#include <sge/src/systems/modules/input/cursor_modifier.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_unique_ptr.hpp>
#include <sge/src/systems/modules/input/object.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/src/systems/modules/window/system.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/detail/input.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>


sge::systems::modules::input::object::object(
	sge::input::plugin::collection const &_collection,
	sge::log::option_container const &_log_options,
	sge::systems::detail::input const &_parameters,
	sge::systems::modules::window::system const &_window_system,
	sge::systems::modules::window::object const &_window_object
)
:
	input_system_(
		sge::input::create_multi_system(
			_collection,
			_log_options
		)
	),
	input_processor_(
		input_system_->create_processor(
			_window_object.get(),
			_window_system.get()
		)
	),
	cursor_demuxer_(
		_parameters.get_cursor_demuxer().get()
		?
			optional_cursor_unique_ptr(
				fcppt::unique_ptr_to_base<
					sge::input::cursor::object
				>(
					fcppt::make_unique_ptr<
						sge::input::cursor::demuxer
					>(
						*input_processor_
					)
				)
			)
		:
			optional_cursor_unique_ptr()
	),
	keyboard_collector_(
		_parameters.get_keyboard_collector().get()
		?
			optional_keyboard_unique_ptr(
				fcppt::unique_ptr_to_base<
					sge::input::keyboard::device
				>(
					fcppt::make_unique_ptr<
						sge::input::keyboard::collector
					>(
						*input_processor_
					)
				)
			)
		:
			optional_keyboard_unique_ptr()
	),
	mouse_collector_(
		_parameters.get_mouse_collector().get()
		?
			optional_mouse_unique_ptr(
				fcppt::unique_ptr_to_base<
					sge::input::mouse::device
				>(
					fcppt::make_unique_ptr<
						sge::input::mouse::collector
					>(
						*input_processor_
					)
				)
			)
		:
			optional_mouse_unique_ptr()
	),
	cursor_modifier_(
		_parameters.parameters().cursor_options()
		!=
		sge::systems::cursor_option_field::null()
		?
			optional_cursor_modifier_unique_ptr(
				fcppt::make_unique_ptr<
					sge::systems::modules::input::cursor_modifier
				>(
					*input_processor_,
					_parameters.parameters().cursor_options()
				)
			)
		:
			optional_cursor_modifier_unique_ptr()
	)
{
	for(
		sge::input::capabilities const element
		:
		{
			sge::input::capabilities::cursor,
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse
		}
	)
		if(
			!(
				input_system_->capabilities()
				&
				element
			)
		)
		{
			FCPPT_LOG_WARNING(
				sge::systems::logger(),
				fcppt::log::_
					<<
					FCPPT_TEXT("Your input plugins can't handle capability ")
					<<
					sge::input::capabilities_to_string(
						element
					)
			);
		}
}

sge::systems::modules::input::object::~object()
{
}

sge::input::system &
sge::systems::modules::input::object::system() const
{
	return
		*input_system_;
}

sge::input::processor &
sge::systems::modules::input::object::processor() const
{
	return
		*input_processor_;
}

sge::input::cursor::object &
sge::systems::modules::input::object::cursor_demuxer() const
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			cursor_demuxer_
		);
}

sge::input::keyboard::device &
sge::systems::modules::input::object::keyboard_collector() const
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			keyboard_collector_
		);
}

sge::input::mouse::device &
sge::systems::modules::input::object::mouse_collector() const
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			mouse_collector_
		);
}

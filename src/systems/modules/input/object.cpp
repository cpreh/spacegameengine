/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/object_unique_ptr.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/device_unique_ptr.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/device_unique_ptr.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/log/option_container.hpp>
#include <sge/src/systems/logger.hpp>
#include <sge/src/systems/modules/input/cursor_modifier.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_unique_ptr.hpp>
#include <sge/src/systems/modules/input/object.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/src/systems/modules/window/system.hpp>
#include <sge/systems/detail/input.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
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
			sge::input::cursor::object_unique_ptr(
				fcppt::make_unique_ptr<
					sge::input::cursor::demuxer
				>(
					*input_processor_
				)
			)
		:
			sge::input::cursor::object_unique_ptr()
	),
	keyboard_collector_(
		_parameters.get_keyboard_collector().get()
		?
			sge::input::keyboard::device_unique_ptr(
				fcppt::make_unique_ptr<
					sge::input::keyboard::collector
				>(
					*input_processor_
				)
			)
		:
			sge::input::keyboard::device_unique_ptr()
	),
	mouse_collector_(
		_parameters.get_mouse_collector().get()
		?
			sge::input::mouse::device_unique_ptr(
				fcppt::make_unique_ptr<
					sge::input::mouse::collector
				>(
					*input_processor_
				)
			)
		:
			sge::input::mouse::device_unique_ptr()
	),
	cursor_modifier_(
		_parameters.parameters().cursor_options()
		?
			fcppt::make_unique_ptr<
				sge::systems::modules::input::cursor_modifier
			>(
				*input_processor_,
				_parameters.parameters().cursor_options()
			)
		:
			sge::systems::modules::input::cursor_modifier_unique_ptr()
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
	return *input_system_;
}

sge::input::processor &
sge::systems::modules::input::object::processor() const
{
	return *input_processor_;
}

sge::input::cursor::object &
sge::systems::modules::input::object::cursor_demuxer() const
{
	return *cursor_demuxer_;
}

sge::input::keyboard::device &
sge::systems::modules::input::object::keyboard_collector() const
{
	return *keyboard_collector_;
}

sge::input::mouse::device &
sge::systems::modules::input::object::mouse_collector() const
{
	return *mouse_collector_;
}

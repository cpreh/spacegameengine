/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/src/systems/modules/input/cursor_modifier.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_unique_ptr.hpp>
#include <sge/src/systems/modules/input/object.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/systems/detail/input.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::systems::modules::input::object::object(
	sge::input::plugin::collection const &_collection,
	sge::systems::detail::input const &_parameters,
	sge::systems::modules::window::object const &_window
)
:
	input_system_(
		sge::input::create_multi_system(
			_collection
		)
	),
	input_processor_(
		input_system_->create_processor(
			_window.window(),
			_window.system()
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

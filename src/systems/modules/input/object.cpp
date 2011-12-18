/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/plugin.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system.hpp>
#include <sge/input/cursor/demuxer.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/add_plugin.hpp>
#include <sge/src/systems/plugin_cache_fwd.hpp>
#include <sge/src/systems/modules/input/cursor_modifier.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_unique_ptr.hpp>
#include <sge/src/systems/modules/input/object.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::systems::modules::input::object::object(
	sge::systems::plugin_cache &_plugin_cache,
	sge::plugin::manager &_manager,
	sge::systems::input const &_parameters,
	sge::systems::modules::window::object const &_window
)
:
	input_plugin_(
		sge::systems::add_plugin(
			_plugin_cache,
			_manager.plugin<
				sge::input::system
			>().load()
		)
	),
	input_system_(
		input_plugin_->get()()
	),
	input_processor_(
		input_system_->create_processor(
			_window.window(),
			_window.system()
		)
	),
	cursor_demuxer_(
		(
			_parameters.input_helpers()
			&
			sge::systems::input_helper::cursor_demuxer
		)
		?
			fcppt::make_shared_ptr<
				sge::input::cursor::demuxer
			>(
				fcppt::ref(
					*input_processor_
				)
			)
		:
			sge::input::cursor::object_ptr()
	),
	keyboard_collector_(
		(
			_parameters.input_helpers()
			&
			systems::input_helper::keyboard_collector
		)
		?
			fcppt::make_shared_ptr<
				sge::input::keyboard::collector
			>(
				fcppt::ref(
					*input_processor_
				)
			)
		:
			sge::input::keyboard::device_ptr()
	),
	mouse_collector_(
		(
			_parameters.input_helpers()
			&
			systems::input_helper::mouse_collector
		)
		?
			fcppt::make_shared_ptr<
				sge::input::mouse::collector
			>(
				fcppt::ref(
					*input_processor_
				)
			)
		:
			sge::input::mouse::device_ptr()
	),
	cursor_modifier_(
		_parameters.cursor_options()
		?
			fcppt::make_unique_ptr<
				sge::systems::modules::input::cursor_modifier
			>(
				fcppt::ref(
					*input_processor_
				),
				_parameters.cursor_options()
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

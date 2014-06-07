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


#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/src/systems/modules/window/base.hpp>
#include <sge/src/systems/modules/window/original.hpp>
#include <sge/window/create_from_awl.hpp>
#include <sge/window/object.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <awl/cursor/create_predefined.hpp>
#include <awl/cursor/object.hpp>
#include <awl/cursor/predefined.hpp>
#include <awl/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/create_processor.hpp>
#include <awl/window/event/processor.hpp>


sge::systems::modules::window::original::original(
	sge::window::parameters const &_parameters,
	sge::window::system &_system,
	sge::systems::modules::renderer::optional_system_ref const &_renderer_system
)
:
	sge::systems::modules::window::base(),
	awl_visual_(
		_renderer_system
		?
			_renderer_system->create_visual()
		:
			_system.awl_system().default_visual()
	),
	awl_cursor_(
		_parameters.cursor()
		?
			awl::cursor::object_unique_ptr()
		:
			awl::cursor::create_predefined(
				_system.awl_system(),
				awl::cursor::predefined::arrow
			)
	),
	awl_window_(
		sge::window::create_from_awl(
			_system.awl_system(),
			*awl_visual_,
			awl_cursor_
			?
				sge::window::parameters(
					_parameters
				)
				.cursor(
					*awl_cursor_
				)
			:
				_parameters
		)
	),
	awl_window_event_processor_(
		awl::window::event::create_processor(
			*awl_window_
		)
	),
	window_(
		_system.create(
			*awl_window_,
			*awl_window_event_processor_
		)
	)
{
}

sge::systems::modules::window::original::~original()
{
}

sge::window::object &
sge::systems::modules::window::original::get() const
{
	return
		*window_;
}

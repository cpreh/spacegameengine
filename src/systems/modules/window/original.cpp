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


#include <sge/src/systems/modules/window/original.hpp>
#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/window/create_from_awl.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/parameters_fwd.hpp>
#include <sge/window/system.hpp>
#include <awl/event/create_processor.hpp>
#include <awl/event/processor.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/create_processor.hpp>
#include <awl/system/event/optional_processor_ref.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/window/instance.hpp>
#include <awl/window/event/create_processor.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/optional_impl.hpp>


sge::systems::modules::window::original::original(
	sge::window::parameters const &_parameters,
	sge::systems::modules::renderer::optional_system_ref const &_renderer_system
)
:
	awl_system_(
		awl::system::create()
	),
	awl_system_event_processor_(
		awl::system::event::create_processor(
			*awl_system_
		)
	),
	awl_event_processor_(
		awl::event::create_processor(
			*awl_system_,
			awl::system::event::optional_processor_ref(
				*awl_system_event_processor_
			)
		)
	),
	awl_window_(
		_renderer_system
		?
			_renderer_system->create_window(
				*awl_system_,
				_parameters
			)
		:
			sge::window::create_from_awl(
				*awl_system_,
				_parameters
			)
	),
	awl_window_event_processor_(
		awl::window::event::create_processor(
			*awl_window_
		)
	),
	system_(
		*awl_system_,
		*awl_system_event_processor_,
		*awl_event_processor_
	),
	window_(
		system_.create(
			*awl_window_,
			*awl_window_event_processor_
		)
	)
{
}

sge::systems::modules::window::original::~original()
{
}

sge::window::system &
sge::systems::modules::window::original::system()
{
	return system_;
}

sge::window::object &
sge::systems::modules::window::original::window() const
{
	return *window_;
}

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


#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/object.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/system.hpp>
#include <sge/src/systems/add_plugin.hpp>
#include <sge/src/systems/plugin_by_name.hpp>
#include <sge/src/systems/plugin_cache_fwd.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/window/parameters_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/instance_shared_ptr.hpp>


sge::systems::modules::renderer::system::system(
	sge::systems::plugin_cache &_plugin_cache,
	sge::plugin::manager &_plugin_manager,
	sge::systems::renderer const &_parameters
)
:
	plugin_(
		sge::systems::add_plugin(
			_plugin_cache,
			sge::systems::plugin_by_name<
				sge::renderer::system
			>(
				_plugin_manager,
				_parameters.name()
			)
		)
	),
	renderer_parameters_(
		_parameters.parameters()
	),
	renderer_system_(
		plugin_->get()()
	)
{
}

awl::window::instance_shared_ptr const
sge::systems::modules::renderer::system::create_window(
	awl::system::object &_awl_system,
	sge::window::parameters const &_parameters
)
{
	return
		renderer_system_->create_window(
			_awl_system,
			_parameters,
			renderer_parameters_
		);
}

sge::renderer::system &
sge::systems::modules::renderer::system::get() const
{
	return *renderer_system_;
}

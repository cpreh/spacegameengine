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


#include <sge/renderer/system.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/src/systems/modules/renderer/create_device.hpp>
#include <sge/src/systems/modules/renderer/system.hpp>
#include <sge/src/systems/modules/window/object.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/window/object.hpp>


sge::renderer::device::core_unique_ptr
sge::systems::modules::renderer::create_device(
	sge::systems::detail::renderer const &_parameters,
	sge::systems::modules::renderer::system const &_system,
	sge::systems::modules::window::object const &_window
)
{
	sge::renderer::device::parameters const parameters(
		_parameters.parameters().device_index(),
		_parameters.parameters().display_mode(),
		_window.get().awl_object(),
		_window.get().awl_window_event_processor()
	);

	return
		(
			_parameters.caps()
			==
			sge::systems::renderer_caps::ffp
		)
		?
			sge::renderer::device::core_unique_ptr(
				_system.get().create_ffp_renderer(
					parameters
				)
			)
		:
			_system.get().create_core_renderer(
				parameters
			)
		;
}

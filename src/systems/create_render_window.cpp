/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "create_render_window.hpp"
#include <sge/renderer/system.hpp>
#include <sge/renderer/window_parameters.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/create.hpp>
#include <sge/window/parameters.hpp>

sge::window::instance_ptr const
sge::systems::create_render_window(
	awl::window::system_ptr const _awl_sys,
	sge::renderer::system_ptr const _render_sys,
	sge::systems::window const &_window_param,
	sge::renderer::parameters const &_render_param
)
{
	return
		sge::window::create(
			sge::window::parameters(
				_render_sys->create_window(
					_awl_sys,
					_window_param.parameter().get<
						sge::renderer::window_parameters
					>(),
					_render_param
				)
			)
			.event_processor(
				_window_param.event_processor()
			)
			.io_service(
				_window_param.io_service()
			)
		);
}

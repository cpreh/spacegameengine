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


#include <sge/src/systems/wrap_window.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/wrapped_window.hpp>
#include <sge/window/create.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/window/parameters.hpp>


sge::window::instance_ptr const
sge::systems::wrap_window(
	sge::systems::window const &_param
)
{
	sge::systems::wrapped_window const &wrapped(
		_param.parameter().get<
			sge::systems::wrapped_window
		>()
	);

	return
		sge::window::create(
			sge::window::parameters(
				wrapped.system(),
				wrapped.window()
			)
			.window_event_processor(
				_param.window_event_processor()
			)
			.io_service(
				_param.io_service()
			)
		);
}

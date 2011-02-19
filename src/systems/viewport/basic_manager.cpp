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


#include "basic_manager.hpp"
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/window/instance.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>

sge::systems::viewport::basic_manager::basic_manager(
	sge::renderer::device_ptr const _device,
	systems::viewport::resize_function const &_resize_function
)
:
	device_(
		_device
	),
	target_(
		_device->onscreen_target()
	),
	resize_function_(
		_resize_function
	),
	resize_connection_(
		_device->window()->awl_window_event_processor()->resize_callback(
			std::tr1::bind(
				&basic_manager::on_resize,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	manage_signal_()
{
}

sge::systems::viewport::basic_manager::~basic_manager()
{
}

fcppt::signal::auto_connection
sge::systems::viewport::basic_manager::manage_callback(
	systems::viewport::manage_callback const &_callback
)
{
	return
		manage_signal_.connect(
			_callback
		);
}

void
sge::systems::viewport::basic_manager::on_resize(
	awl::window::event::resize const &_resize
)
{
	target_->viewport(
		resize_function_(
			_resize
		)
	);

	manage_signal_(
		device_
	);
}

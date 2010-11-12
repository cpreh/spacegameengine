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


#include "center.hpp"
#include "resize_manager.hpp"
#include <sge/renderer/device.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/window/instance.hpp>
#include <awl/event/processor.hpp>
#include <awl/event/resize.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>

sge::systems::viewport::resize_manager::resize_manager(
	sge::renderer::device_ptr const _device
)
:
	device_(
		_device
	),
	target_(
		_device->target()
	),
	resize_connection_(
		_device->window()->awl_event_processor()->resize_callback(
			std::tr1::bind(
				&resize_manager::on_resize,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}


sge::systems::viewport::resize_manager::~resize_manager()
{
}

void
sge::systems::viewport::resize_manager::on_resize(
	awl::event::resize const &_resize
)
{
	target_->viewport(
		sge::renderer::viewport(
			viewport::center(
				device_->screen_size(),
				fcppt::math::dim::structure_cast<
					sge::window::dim_type
				>(
					_resize.dim()
				)
			)
		)
	);
}

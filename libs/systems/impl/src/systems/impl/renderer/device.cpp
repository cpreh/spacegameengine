/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/impl/renderer/create_device.hpp>
#include <sge/systems/impl/renderer/device.hpp>
#include <sge/systems/impl/renderer/system_fwd.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <fcppt/cast/static_downcast.hpp>


sge::systems::impl::renderer::device::device(
	sge::systems::detail::renderer const &_parameters,
	sge::systems::impl::renderer::system const &_system,
	sge::systems::impl::window::object const &_window
)
:
	renderer_device_(
		sge::systems::impl::renderer::create_device(
			_parameters,
			_system,
			_window
		)
	),
	viewport_manager_(
		*renderer_device_,
		_window.get(),
		_parameters.parameters().resize_callback()
	)
{
}

sge::systems::impl::renderer::device::~device()
{
}

sge::renderer::device::ffp &
sge::systems::impl::renderer::device::get_ffp() const
{
	return
		fcppt::cast::static_downcast<
			sge::renderer::device::ffp &
		>(
			this->get_core()
		);
}

sge::renderer::device::core &
sge::systems::impl::renderer::device::get_core() const
{
	return
		*renderer_device_;
}

sge::viewport::manager &
sge::systems::impl::renderer::device::viewport_manager()
{
	return
		viewport_manager_;
}

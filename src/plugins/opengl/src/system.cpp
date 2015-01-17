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


#include <sge/opengl/device.hpp>
#include <sge/opengl/get_device_caps.hpp>
#include <sge/opengl/system.hpp>
#include <sge/opengl/backend/create_system.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/platform/create_system.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>


sge::opengl::system::system(
	awl::system::object &_awl_system
)
:
	system_context_(),
	platform_system_(
		sge::opengl::platform::create_system(
			_awl_system
		)
	),
	backend_system_(
		sge::opengl::backend::create_system(
			system_context_,
			_awl_system
		)
	),
	caps_(
		sge::opengl::get_device_caps(
			_awl_system,
			system_context_,
			*backend_system_
		)
	)
{
}

sge::opengl::system::~system()
{
}

sge::renderer::device::core_unique_ptr
sge::opengl::system::create_core_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	return
		sge::renderer::device::core_unique_ptr(
			this->create_ffp_renderer(
				_parameters
			)
		);
}

sge::renderer::device::ffp_unique_ptr
sge::opengl::system::create_ffp_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	FCPPT_ASSERT_PRE(
		_parameters.index().get()
		<
		this->device_count().get()
	);

	return
		sge::renderer::device::ffp_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::device
			>(
				_parameters.display_mode(),
				_parameters.window(),
				_parameters.window_processor(),
				*platform_system_,
				*backend_system_,
				system_context_,
				caps_
			)
		);
}

awl::visual::object_unique_ptr
sge::opengl::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		backend_system_->create_visual(
			_pixel_format
		);
}

sge::renderer::caps::device_count const
sge::opengl::system::device_count() const
{
	return
		platform_system_->device_count();
}

sge::renderer::caps::device const &
sge::opengl::system::device_caps(
	sge::renderer::device::index const _index
) const
{
	FCPPT_ASSERT_PRE(
		_index.get()
		<
		this->device_count().get()
	);

	return
		caps_;
}

sge::renderer::display_mode::container
sge::opengl::system::display_modes(
	sge::renderer::device::index const _index
) const
{
	return
		platform_system_->display_modes(
			_index
		);
}

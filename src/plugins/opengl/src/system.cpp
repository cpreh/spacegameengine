/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/create_device_caps.hpp>
#include <sge/opengl/device.hpp>
#include <sge/opengl/system.hpp>
#include <sge/opengl/device_state/create_system.hpp>
#include <sge/opengl/device_state/system.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>


sge::opengl::system::system()
:
	system_context_(),
	device_system_(
		sge::opengl::device_state::create_system(
			system_context_
		)
	),
	caps_(
		sge::opengl::create_device_caps(
			system_context_,
			*device_system_
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
		_parameters.adapter().get()
		<
		this->device_count().get()
	);

	return
		sge::renderer::device::ffp_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::device
			>(
				fcppt::cref(
					_parameters.params()
				),
				fcppt::ref(
					_parameters.window()
				),
				fcppt::ref(
					*device_system_
				),
				fcppt::ref(
					system_context_
				),
				fcppt::cref(
					*caps_
				)
			)
		);
}

awl::visual::object_unique_ptr
sge::opengl::system::create_visual(
	awl::system::object &_awl_system,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		device_system_->create_visual(
			_awl_system,
			_pixel_format
		);
}

sge::renderer::caps::system_field const
sge::opengl::system::caps() const
{
	return
		sge::renderer::caps::system_field(
			sge::renderer::caps::system::opengl
		)
		|
		sge::renderer::caps::system::ffp;
}

sge::renderer::caps::device_count const
sge::opengl::system::device_count() const
{
	return
		sge::renderer::caps::device_count(
			1u
		);
}

sge::renderer::caps::device const &
sge::opengl::system::device_caps(
	sge::renderer::adapter const _adapter
) const
{
	FCPPT_ASSERT_PRE(
		_adapter.get()
		<
		this->device_count().get()
	);

	return
		*caps_;
}

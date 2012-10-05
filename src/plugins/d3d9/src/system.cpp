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


#include <sge/d3d9/create_device_caps.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/system.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


sge::d3d9::system::system()
:
	system_(
		::Direct3DCreate9(
			D3D_SDK_VERSION
		)
	),
	caps_()
{
	if(
		!system_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Initialization of d3d failed!")
		);

	UINT const adapters(
		system_->GetAdapterCount()
	);

	for(
		sge::renderer::adapter adapter(
			0u
		);
		adapter.get() < adapters;
		++adapter
	)
		fcppt::container::ptr::push_back_unique_ptr(
			caps_,
			sge::d3d9::create_device_caps(
				*system_,
				adapter
			)
		);
}

sge::d3d9::system::~system()
{
}

sge::renderer::device::core_unique_ptr
sge::d3d9::system::create_core_renderer(
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
sge::d3d9::system::create_ffp_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	return
		sge::renderer::device::ffp_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::device
			>(
				fcppt::ref(
					*system_
				),
				fcppt::cref(
					_parameters
				),
				fcppt::cref(
					this->device_caps(
						_parameters.adapter()
					)
				)
			)
		);
}

awl::visual::object_unique_ptr
sge::d3d9::system::create_visual(
	awl::system::object &_awl_system,
	sge::renderer::pixel_format::object const &
)
{
	return
		_awl_system.default_visual();
}

sge::renderer::caps::system_field const
sge::d3d9::system::caps() const
{
	return
		sge::renderer::caps::system_field(
			sge::renderer::caps::system::ffp
		);
}

sge::renderer::caps::device_count const
sge::d3d9::system::device_count() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::caps::device_count
		>(
			caps_.size()
		);
}

sge::renderer::caps::device const &
sge::d3d9::system::device_caps(
	sge::renderer::adapter const _adapter
) const
{
	return
		caps_[
			_adapter.get()
		];
}

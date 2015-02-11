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


#include <sge/d3d9/create.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/get_device_caps.hpp>
#include <sge/d3d9/get_display_modes.hpp>
#include <sge/d3d9/logger.hpp>
#include <sge/d3d9/system.hpp>
#include <sge/d3d9/visual.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/int_range_impl.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/object.hpp>


sge::d3d9::system::system()
:
	system_(
		sge::d3d9::create()
	),
	caps_(
		fcppt::algorithm::map<
			sge::d3d9::system::caps_vector
		>(
			this->adapter_range(),
			[
				this
			](
				UINT const _index
			)
			{
				return
					sge::d3d9::get_device_caps(
						*system_,
						sge::renderer::device::index(
							_index
						)
					);
			}
		)
	),
	display_modes_(
		fcppt::algorithm::map<
			sge::d3d9::system::display_mode_container_vector
		>(
			this->adapter_range(),
			[
				this
			](
				UINT const _index
			)
			{
				return
					sge::d3d9::get_display_modes(
						*system_,
						sge::renderer::device::index(
							_index
						)
					);
			}
		)
	)
{
	if(
		!sge::d3d9::logger().activated(
			fcppt::log::level::debug
		)
	)
		return;


	sge::renderer::device::index index(
		0u
	);

	for(
		sge::renderer::display_mode::container const &modes
		:
		display_modes_
	)
	{
		FCPPT_LOG_DEBUG(
			sge::d3d9::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Display modes for device ")
				<< index++
		);

		for(
			sge::renderer::display_mode::object const &mode
			:
			modes
		)
			FCPPT_LOG_DEBUG(
				sge::d3d9::logger(),
				fcppt::log::_
					<< mode
			);
	}
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
				*system_,
				_parameters,
				this->device_caps(
					_parameters.index()
				)
			)
		);
}

awl::visual::object_unique_ptr
sge::d3d9::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		fcppt::make_unique_ptr<
			sge::d3d9::visual
		>(
			_pixel_format
		);
}

sge::renderer::caps::device_count const
sge::d3d9::system::device_count() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::caps::device_count,
			fcppt::cast::size_fun
		>(
			caps_.size()
		);
}

sge::renderer::caps::device const &
sge::d3d9::system::device_caps(
	sge::renderer::device::index const _index
) const
{
	return
		caps_[
			_index.get()
		];
}

sge::renderer::display_mode::container
sge::d3d9::system::display_modes(
	sge::renderer::device::index const _index
) const
{
	return
		display_modes_[
			_index.get()
		];
}

sge::d3d9::system::device_index_range const
sge::d3d9::system::adapter_range() const
{
	return
		fcppt::make_int_range_count(
			system_->GetAdapterCount()
		);
}

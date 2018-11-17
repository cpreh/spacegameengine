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


#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/make_ref.hpp>


sge::opencl::context::parameters::parameters(
	sge::opencl::platform::object &_platform,
	sge::opencl::device::object_ref_sequence const &_device_refs
)
:
	platform_(
		_platform
	),
	device_refs_(
		_device_refs
	),
	error_callback_(),
	shared_renderer_()
{
}

sge::opencl::context::parameters &
sge::opencl::context::parameters::error_callback(
	sge::opencl::context::error_callback const &_error_callback
)
{
	error_callback_ =
		sge::opencl::context::optional_error_callback(
			_error_callback
		);

	return
		*this;
}

sge::opencl::context::parameters &
sge::opencl::context::parameters::share_with(
	sge::renderer::device::core &_shared_renderer
)
{
	shared_renderer_ =
		optional_renderer(
			fcppt::make_ref(
				_shared_renderer
			)
		);

	return
		*this;
}

sge::opencl::device::object_ref_sequence const &
sge::opencl::context::parameters::device_refs() const
{
	return
		device_refs_;
}

sge::opencl::context::optional_error_callback const &
sge::opencl::context::parameters::error_callback() const
{
	return
		error_callback_;
}

sge::opencl::context::parameters::optional_renderer const &
sge::opencl::context::parameters::shared_renderer() const
{
	return
		shared_renderer_;
}

sge::opencl::platform::object &
sge::opencl::context::parameters::platform() const
{
	return
		platform_.get();
}

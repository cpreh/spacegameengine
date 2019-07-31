//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

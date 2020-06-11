//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/impl/renderer/create_device.hpp>
#include <sge/systems/impl/renderer/device.hpp>
#include <sge/systems/impl/renderer/system_fwd.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <fcppt/make_ref.hpp>
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
		fcppt::make_ref(
			*renderer_device_
		),
		fcppt::make_ref(
			_window.get()
		),
		sge::viewport::optional_resize_callback{
			_parameters.parameters().resize_callback()
		}
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

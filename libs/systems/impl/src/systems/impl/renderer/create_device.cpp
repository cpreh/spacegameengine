//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/system.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/impl/renderer/create_device.hpp>
#include <sge/systems/impl/renderer/system.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::device::core_unique_ptr
sge::systems::impl::renderer::create_device(
	sge::systems::detail::renderer const &_parameters,
	sge::systems::impl::renderer::system const &_system,
	sge::systems::impl::window::object const &_window
)
{
	sge::renderer::device::parameters const parameters(
		_parameters.parameters().display_mode(),
		fcppt::make_ref(
			_window.get()
		)
	);

	return
		(
			_parameters.caps()
			==
			sge::systems::renderer_caps::ffp
		)
		?
			fcppt::unique_ptr_to_base<
				sge::renderer::device::core
			>(
				_system.get().create_ffp_renderer(
					parameters
				)
			)
		:
			_system.get().create_core_renderer(
				parameters
			)
		;
}

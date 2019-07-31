//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/wrapped_window_fwd.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/base_unique_ptr.hpp>
#include <sge/systems/impl/window/make_base.hpp>
#include <sge/systems/impl/window/original.hpp>
#include <sge/systems/impl/window/wrapped.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/variant/match.hpp>


sge::systems::impl::window::base_unique_ptr
sge::systems::impl::window::make_base(
	sge::systems::window const &_parameters,
	sge::window::system &_system,
	sge::systems::impl::renderer::optional_system_ref const &_renderer_system
)
{
	return
		fcppt::variant::match(
			_parameters.source(),
			[
				&_system,
				&_renderer_system
			](
				sge::systems::original_window const &_original
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::systems::impl::window::base
					>(
						fcppt::make_unique_ptr<
							sge::systems::impl::window::original
						>(
							_original,
							_system,
							_renderer_system
						)
					);
			},
			[
				&_system
			](
				sge::systems::wrapped_window const &_wrapped
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::systems::impl::window::base
					>(
						fcppt::make_unique_ptr<
							sge::systems::impl::window::wrapped
						>(
							_wrapped,
							_system
						)
					);
			}
		);
}

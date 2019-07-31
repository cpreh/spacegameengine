//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/core.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/plugin/collection.hpp>
#include <sge/renderer/plugin/context.hpp>
#include <sge/renderer/plugin/iterator.hpp>
#include <sge/renderer/plugin/traits.hpp>
#include <sge/systems/optional_name_fwd.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/impl/find_plugin.hpp>
#include <sge/systems/impl/renderer/find_plugin.hpp>
#include <sge/systems/impl/renderer/plugin_core_pair.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::systems::impl::renderer::plugin_core_pair
sge::systems::impl::renderer::find_plugin(
	fcppt::log::context &_log_context,
	sge::renderer::plugin::collection const &_collection,
	sge::systems::optional_name const &_name,
	sge::renderer::caps::system_field const &_caps,
	sge::systems::renderer_caps const _renderer_caps
)
{
	return
		sge::systems::impl::find_plugin<
			sge::renderer::core
		>(
			_log_context,
			_collection,
			_name,
			[
				_renderer_caps,
				&_caps
			](
				sge::renderer::core const &_core
			)
			{
				return
					fcppt::container::bitfield::is_subset_eq(
						_renderer_caps
						==
						sge::systems::renderer_caps::ffp
						?
							_caps
							|
							sge::renderer::caps::system::ffp
						:
							_caps
						,
						_core.caps()
					);
			}
		);
}

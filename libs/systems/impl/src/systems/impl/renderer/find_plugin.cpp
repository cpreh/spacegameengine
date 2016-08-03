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


#include <sge/renderer/core.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
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

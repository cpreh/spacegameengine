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


#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/renderer/plugin.hpp>
#include <sge/renderer/plugin_shared_ptr.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/systems/exception.hpp>
#include <sge/src/systems/modules/renderer/find_plugin.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>


sge::renderer::plugin_shared_ptr const
sge::systems::modules::renderer::find_plugin(
	sge::plugin::manager &_manager,
	sge::renderer::caps::system_field const &_caps
)
{
	typedef sge::plugin::iterator<
		sge::renderer::system
	> iterator;

	for(
		iterator it(
			_manager.begin<
				sge::renderer::system
			>()
		);
		it
		!=
		_manager.end<
			sge::renderer::system
		>();
		++it
	)
	{
		sge::renderer::plugin_shared_ptr const plugin(
			it->load()
		);

		if(
			fcppt::container::bitfield::is_subset_eq(
				_caps,
				plugin->get()()->caps()
			)
		)
			return
				plugin;
	}

	throw sge::systems::exception(
		FCPPT_TEXT("Renderer plugin with requested caps not found!")
	);
}

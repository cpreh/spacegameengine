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


#include <sge/input/plugin.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/plugin_cache.hpp>
#include <sge/src/systems/modules/input/cached_plugins.hpp>


sge::systems::modules::input::cached_plugins::cached_plugins(
	sge::systems::plugin_cache &_cache,
	sge::plugin::manager &_manager
)
{
	typedef sge::plugin::iterator<
		sge::input::system
	> plugin_iterator;

	for(
		plugin_iterator it(
			_manager.begin<
				sge::input::system
			>()
		);
		it
		!=
		_manager.end<
			sge::input::system
		>();
		++it
	)
		_cache.add(
			it->load()
		);
}

sge::systems::modules::input::cached_plugins::~cached_plugins()
{
}

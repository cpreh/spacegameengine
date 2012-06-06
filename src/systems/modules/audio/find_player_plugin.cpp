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


#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/src/systems/find_plugin.hpp>
#include <sge/src/systems/plugin_cache_fwd.hpp>
#include <sge/src/systems/modules/audio/find_player_plugin.hpp>
#include <sge/src/systems/modules/audio/player_pair.hpp>
#include <sge/systems/audio_player.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <fcppt/config/external_end.hpp>


sge::systems::modules::audio::player_pair const
sge::systems::modules::audio::find_player_plugin(
	sge::systems::plugin_cache &_plugin_cache,
	sge::plugin::manager &_manager,
	sge::systems::audio_player const &_parameters
)
{
	return
		sge::systems::find_plugin<
			sge::audio::player
		>(
			_plugin_cache,
			_manager,
			boost::phoenix::bind(
				&sge::audio::player::capabilities,
				boost::phoenix::arg_names::arg1
			)
			==
			_parameters.capabilities()
		);
}

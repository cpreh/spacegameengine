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
#include <sge/audio/player_ptr.hpp>
#include <sge/audio/player_plugin.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/modules/audio/find_player_plugin.hpp>
#include <sge/src/systems/modules/audio/player_pair.hpp>
#include <sge/systems/audio_player.hpp>
#include <sge/systems/exception.hpp>
#include <fcppt/text.hpp>


sge::systems::modules::audio::player_pair const
sge::systems::modules::audio::find_player_plugin(
	sge::plugin::manager &_manager,
	sge::systems::audio_player const &_parameters
)
{
	for(
		plugin::iterator<sge::audio::player> it(
			_manager.begin<sge::audio::player>()
		);
		it != _manager.end<sge::audio::player>();
		++it
	)
	{
		typedef sge::plugin::context<
			sge::audio::player
		>::ptr_type plugin_ptr;

		plugin_ptr const plugin(
			it->load()
		);

		sge::audio::player_ptr const player(
			plugin->get()()
		);

		if(
			player->capabilities() == _parameters.capabilities()
		)
			return
				sge::systems::modules::audio::player_pair(
					plugin,
					player
				);
	}

	throw sge::systems::exception(
		FCPPT_TEXT("No audio player satisfied the audio player capabilities.")
	);
}

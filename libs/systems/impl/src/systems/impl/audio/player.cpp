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


#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin/collection_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/impl/audio/find_player_plugin.hpp>
#include <sge/systems/impl/audio/player.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::systems::impl::audio::player::player(
	fcppt::log::context &_log_context,
	fcppt::log::object &_log,
	sge::audio::player_plugin::collection const &_collection,
	sge::systems::audio_player const &_parameters
)
:
	player_pair_(
		sge::systems::impl::audio::find_player_plugin(
			_log_context,
			_log,
			_collection,
			_parameters
		)
	)
{
}

sge::systems::impl::audio::player::~player()
{
}


sge::audio::player &
sge::systems::impl::audio::player::get() const
{
	return
		player_pair_.system();
}

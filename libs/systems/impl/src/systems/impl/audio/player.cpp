//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

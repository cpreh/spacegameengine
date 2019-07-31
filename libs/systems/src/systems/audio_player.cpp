//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/name.hpp>
#include <sge/systems/audio_player.hpp>
#include <sge/systems/optional_name.hpp>


sge::systems::audio_player::audio_player()
:
	name_()
{
}

sge::systems::audio_player &
sge::systems::audio_player::name(
	sge::plugin::name const &_name
)
{
	name_ =
		sge::systems::optional_name(
			_name
		);

	return
		*this;
}

sge::systems::optional_name const &
sge::systems::audio_player::name() const
{
	return
		name_;
}

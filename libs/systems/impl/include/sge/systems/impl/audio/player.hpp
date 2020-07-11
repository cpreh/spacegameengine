//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/audio/player_fwd.hpp>
#include <sge/audio/player_plugin/collection_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/impl/audio/player_fwd.hpp>
#include <sge/systems/impl/audio/player_pair.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace audio
{

class player
{
	FCPPT_NONMOVABLE(
		player
	);
public:
	player(
		fcppt::log::context_reference,
		fcppt::log::object &, // NOLINT(google-runtime-references)
		sge::audio::player_plugin::collection const &,
		sge::systems::audio_player const &
	);

	~player();

	[[nodiscard]]
	sge::audio::player &
	get() const;
private:
	sge::systems::impl::audio::player_pair const player_pair_;
};

}
}
}
}

#endif

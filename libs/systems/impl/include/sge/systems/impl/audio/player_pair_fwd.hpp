//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_AUDIO_PLAYER_PAIR_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_AUDIO_PLAYER_PAIR_FWD_HPP_INCLUDED

#include <sge/audio/player_fwd.hpp>
#include <sge/systems/impl/plugin_pair_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace audio
{

typedef
sge::systems::impl::plugin_pair<
	sge::audio::player
>
player_pair;

}
}
}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WITH_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/with_audio_player_fwd.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::systems
{

struct with_audio_player
{
	using
	needs_init
	=
	std::true_type;

	using
	parameter_type
	=
	sge::systems::audio_player;

	using
	needs_before
	=
	fcppt::mpl::list::object<>;
};

}

#endif

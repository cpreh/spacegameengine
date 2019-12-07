//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WITH_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/with_audio_player_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

struct with_audio_player
{
	typedef
	std::true_type
	needs_init;

	typedef
	sge::systems::audio_player
	parameter_type;

	typedef
	metal::list<>
	needs_before;
};

}
}

#endif

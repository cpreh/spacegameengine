//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_PLAYER_PLUGIN_OBJECT_FWD_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_PLUGIN_OBJECT_FWD_HPP_INCLUDED

#include <sge/audio/player_fwd.hpp>
#include <sge/plugin/object.hpp>


namespace sge
{
namespace audio
{
namespace player_plugin
{

using
object
=
sge::plugin::object<
	sge::audio::player
>;

}
}
}

#endif

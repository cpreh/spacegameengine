//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_SOUND_PLAY_STATUS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_PLAY_STATUS_HPP_INCLUDED

#include <sge/audio/sound/play_status_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::audio::sound
{

enum class play_status : std::uint8_t
{
  stopped,
  playing,
  paused
};

}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_SOUND_REPEAT_HPP_INCLUDED
#define SGE_AUDIO_SOUND_REPEAT_HPP_INCLUDED

#include <sge/audio/sound/repeat_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::audio::sound
{

enum class repeat : std::uint8_t
{
  once,
  loop
};

}

#endif

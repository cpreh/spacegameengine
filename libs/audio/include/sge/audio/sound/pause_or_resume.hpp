//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_SOUND_PAUSE_OR_RESUME_HPP_INCLUDED
#define SGE_AUDIO_SOUND_PAUSE_OR_RESUME_HPP_INCLUDED

#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/base_fwd.hpp>
#include <sge/audio/sound/do_pause.hpp>


namespace sge
{
namespace audio
{
namespace sound
{

SGE_AUDIO_DETAIL_SYMBOL
void
pause_or_resume(
	sge::audio::sound::base &, // NOLINT(google-runtime-references)
	sge::audio::sound::do_pause
);

}
}
}

#endif

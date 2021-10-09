//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_SOUND_POSITIONAL_UNIQUE_PTR_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_UNIQUE_PTR_HPP_INCLUDED

#include <sge/audio/sound/positional_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge::audio::sound
{

using positional_unique_ptr = fcppt::unique_ptr<sge::audio::sound::positional>;

}

#endif

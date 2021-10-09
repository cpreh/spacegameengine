//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_PLAYER_SHARED_PTR_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_SHARED_PTR_HPP_INCLUDED

#include <sge/audio/player_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>

namespace sge
{
namespace audio
{

using player_shared_ptr = fcppt::shared_ptr<sge::audio::player>;

}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_SOUND_OPTIONAL_DIRECTION_FWD_HPP_INCLUDED
#define SGE_AUDIO_SOUND_OPTIONAL_DIRECTION_FWD_HPP_INCLUDED

#include <sge/audio/vector_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace audio
{
namespace sound
{

typedef
fcppt::optional::object<
	sge::audio::vector
>
optional_direction;

}
}
}

#endif

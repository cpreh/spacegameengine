//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_VECTOR2_TO_VECTOR_HPP_INCLUDED
#define SGE_AUDIO_VECTOR2_TO_VECTOR_HPP_INCLUDED

#include <sge/audio/vector.hpp>
#include <sge/audio/vector2_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>


namespace sge::audio
{

SGE_AUDIO_DETAIL_SYMBOL
sge::audio::vector
vector2_to_vector(
	sge::audio::vector2 const &
);

}

#endif

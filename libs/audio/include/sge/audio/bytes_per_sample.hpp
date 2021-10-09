//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_BYTES_PER_SAMPLE_HPP_INCLUDED
#define SGE_AUDIO_BYTES_PER_SAMPLE_HPP_INCLUDED

#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/detail/symbol.hpp>

namespace sge::audio
{

SGE_AUDIO_DETAIL_SYMBOL
sge::audio::sample_count bytes_per_sample(sge::audio::bits_per_sample);

}

#endif

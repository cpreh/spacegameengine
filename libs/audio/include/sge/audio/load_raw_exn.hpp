//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_LOAD_RAW_EXN_HPP_INCLUDED
#define SGE_AUDIO_LOAD_RAW_EXN_HPP_INCLUDED

#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>

namespace sge::audio
{

SGE_AUDIO_DETAIL_SYMBOL
sge::audio::file_unique_ptr load_raw_exn(
    sge::audio::loader_ref,
    sge::media::const_raw_range const &,
    sge::media::optional_extension const &);

}

#endif

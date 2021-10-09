//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_LOAD_STREAM_RESULT_FWD_HPP_INCLUDED
#define SGE_AUDIO_LOAD_STREAM_RESULT_FWD_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <sge/media/load_stream_result_fwd.hpp>

namespace sge::audio
{

using load_stream_result = sge::media::load_stream_result<sge::audio::file>;

}

#endif

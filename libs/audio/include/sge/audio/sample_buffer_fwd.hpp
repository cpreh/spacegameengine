//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_SAMPLE_BUFFER_FWD_HPP_INCLUDED
#define SGE_AUDIO_SAMPLE_BUFFER_FWD_HPP_INCLUDED

#include <sge/audio/raw_data.hpp>
#include <fcppt/container/buffer/object_fwd.hpp>

namespace sge::audio
{

using sample_buffer = fcppt::container::buffer::object<sge::audio::raw_data>;

}

#endif

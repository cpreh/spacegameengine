//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VORBIS_SEEK_HPP_INCLUDED
#define SGE_VORBIS_SEEK_HPP_INCLUDED

#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/stream_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ogg/os_types.h> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

namespace sge::vorbis
{

// NOLINTNEXTLINE(misc-include-cleaner)
void seek(sge::vorbis::stream &, sge::media::optional_name const &, ogg_int64_t);

}

#endif

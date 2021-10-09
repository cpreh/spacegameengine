//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VORBIS_INFO_HPP_INCLUDED
#define SGE_VORBIS_INFO_HPP_INCLUDED

#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/stream_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/codec.h>
#include <fcppt/config/external_end.hpp>

namespace sge::vorbis
{

vorbis_info info(sge::vorbis::stream &, sge::media::optional_name const &);

}

#endif

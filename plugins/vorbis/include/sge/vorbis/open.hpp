//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VORBIS_OPEN_HPP_INCLUDED
#define SGE_VORBIS_OPEN_HPP_INCLUDED

#include <sge/vorbis/optional_stream_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::vorbis
{

sge::vorbis::optional_stream_unique_ptr open(std::istream &);

}

#endif

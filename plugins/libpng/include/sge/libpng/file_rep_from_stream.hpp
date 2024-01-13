//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_FILE_REP_FROM_STREAM_HPP_INCLUDED
#define SGE_LIBPNG_FILE_REP_FROM_STREAM_HPP_INCLUDED

#include <sge/libpng/optional_file_rep.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::libpng
{

sge::libpng::optional_file_rep file_rep_from_stream(
    fcppt::log::object &, // NOLINT(google-runtime-references)
    std::istream &,
    sge::media::optional_name const &);

}

#endif

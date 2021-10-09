//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/vorbis/callbacks.hpp>
#include <sge/vorbis/open.hpp>
#include <sge/vorbis/optional_stream_unique_ptr.hpp>
#include <sge/vorbis/stream.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/vorbisfile.h>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::vorbis::optional_stream_unique_ptr sge::vorbis::open(std::istream &_stream)
{
  OggVorbis_File ogg_file;

  int const result(::ov_open_callbacks(&_stream, &ogg_file, nullptr, 0L, sge::vorbis::callbacks()));

  return result == 0 ? sge::vorbis::optional_stream_unique_ptr(
                           fcppt::make_unique_ptr<sge::vorbis::stream>(ogg_file))
                     : sge::vorbis::optional_stream_unique_ptr();
}

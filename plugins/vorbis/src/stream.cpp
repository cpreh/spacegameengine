//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/vorbis/stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/vorbisfile.h>
#include <exception>
#include <fcppt/config/external_end.hpp>

sge::vorbis::stream::stream(OggVorbis_File const &_file) : file_(_file) {}

sge::vorbis::stream::~stream()
{
  int const result{::ov_clear(&file_)};

  if(result != 0)
  {
    std::terminate();
  }
}

OggVorbis_File *sge::vorbis::stream::get() { return &file_; }

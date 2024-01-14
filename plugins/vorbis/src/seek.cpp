//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/file_exception.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/error_string.hpp>
#include <sge/vorbis/seek.hpp>
#include <sge/vorbis/stream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ogg/os_types.h> // IWYU pragma: keep
#include <vorbis/vorbisfile.h>
#include <fcppt/config/external_end.hpp>

void sge::vorbis::seek(
    // NOLINTNEXTLINE(misc-include-cleaner)
    sge::vorbis::stream &_stream, sge::media::optional_name const &_name, ogg_int64_t const _pos)
{
  int const error{::ov_pcm_seek(_stream.get(), _pos)};

  if (error != 0)
  {
    throw sge::audio::file_exception{
        _name, FCPPT_TEXT("vorbis: couldn't reset file: ") + sge::vorbis::error_string(error)};
  }
}

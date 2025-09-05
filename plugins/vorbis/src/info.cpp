//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/file_exception.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/info.hpp>
#include <sge/vorbis/stream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <fcppt/config/external_end.hpp>

vorbis_info sge::vorbis::info(sge::vorbis::stream &_stream, sge::media::optional_name const &_name)
{
  vorbis_info const *const info{::ov_info(_stream.get(), -1)};

  if (info == nullptr)
  {
    throw sge::audio::file_exception(
        _name, FCPPT_TEXT("couldn't read file info from ogg vorbis file"));
  }

  return *info;
}

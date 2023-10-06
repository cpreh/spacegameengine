//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/openal/file_format.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

ALenum sge::openal::file_format(sge::audio::file const &_file)
{
  switch (_file.bits_per_sample().get())
  {
  case 8U: // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    switch (_file.channels().get())
    {
    case 1U:
      return AL_FORMAT_MONO8;
    case 2U:
      return AL_FORMAT_STEREO8;
    default: break;
    }
    break;
  case 16U: // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    switch (_file.channels().get())
    {
    case 1U:
      return AL_FORMAT_MONO16;
    case 2U:
      return AL_FORMAT_STEREO16;
    default: break;
    }
    break;
  default: break;
  }

  throw sge::audio::exception(
      FCPPT_TEXT("OpenAL error: Format not supported: ") +
      fcppt::output_to_fcppt_string(_file.bits_per_sample()) + FCPPT_TEXT(" bps, ") +
      fcppt::output_to_fcppt_string(_file.channels()) + FCPPT_TEXT(" channels"));
}

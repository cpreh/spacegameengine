//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/vorbis/callbacks.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ogg/os_types.h> // NOLINT(misc-include-cleaner)
#include <vorbis/vorbisfile.h>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>

namespace
{

std::istream &get_stream(void *const _datasource)
{
  return *fcppt::cast::from_void_ptr<std::istream *>(_datasource);
}

std::size_t ogg_read(
    void *const _ptr, std::size_t const _size, std::size_t const _nmemb, void *const _datasource)
{
  std::istream &stream(get_stream(_datasource));

  if (stream.eof())
  {
    return 0;
  }

  stream.read(
      fcppt::cast::from_void_ptr<char *>(_ptr),
      fcppt::cast::size<std::streamsize>(fcppt::cast::to_signed(_size * _nmemb)));

  if (
      // TODO(philipp): Is this correct?
      stream.bad())
  {
    errno = EBADF;

    return 0U;
  }

  return fcppt::cast::size<std::size_t>(fcppt::cast::to_unsigned(stream.gcount())) / _size;
}

// NOLINTNEXTLINE(misc-include-cleaner)
int ogg_seek(void *const _datasource, ogg_int64_t const _offset, int const _whence)
{
  std::istream &stream(get_stream(_datasource));

  if (stream.eof())
  {
    stream.clear();
  }

  stream.seekg(
      fcppt::cast::size<std::streamoff>(_offset),
      [_whence]
      {
        switch (_whence)
        {
        case SEEK_SET:
          return std::ios_base::beg;
        case SEEK_CUR:
          return std::ios_base::cur;
        case SEEK_END:
          return std::ios_base::end;
        default:
          break;
        }

        FCPPT_ASSERT_UNREACHABLE;
      }());

  return 0;
}

long // NOLINT(google-runtime-int)
ogg_tell(void *const _datasource)
{
  return fcppt::cast::size<long // NOLINT(google-runtime-int)
                           >(get_stream(_datasource).tellg());
}

}

ov_callbacks sge::vorbis::callbacks()
{
  ov_callbacks const callbacks = {&ogg_read, &ogg_seek, nullptr, &ogg_tell};

  return callbacks;
}

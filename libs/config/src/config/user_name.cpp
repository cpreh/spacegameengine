//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/user_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <sge/config/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/dynamic_array.hpp>
#include <fcppt/error/strerrno.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_end.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/config/exception.hpp>
#include <awl/backends/windows/format_message.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <lmcons.h>
#include <windows.h>
#include <fcppt/config/external_end.hpp>
#endif

fcppt::string sge::config::user_name()
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
  using raw_character_sequence = fcppt::array::object<fcppt::char_type, UNLEN + 1>;

  raw_character_sequence raw_characters{fcppt::no_init{}};
  // I don't know if the size argument can be NULL.
  DWORD size{static_cast<DWORD>(raw_characters.size())};

  if (!GetUserName(raw_characters.data(), &size))
  {
    throw sge::config::exception(
        FCPPT_TEXT("Couldn't get user name: ") +
        awl::backends::windows::format_message(GetLastError()));
  }

  return fcppt::string(raw_characters.data());
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
  long const bufsize{// NOLINT(google-runtime-int)
                     sysconf(_SC_GETPW_R_SIZE_MAX)};

  if (bufsize == -1)
  {
    throw sge::config::exception{FCPPT_TEXT("Couldn't determine maximum user name length")};
  }

  using raw_byte_sequence = fcppt::container::dynamic_array<char>;

  raw_byte_sequence buf{fcppt::cast::to_unsigned(bufsize)};

  struct passwd pwd
  {
  };
  struct passwd *result{nullptr};

  int const error_code{getpwuid_r(getuid(), &pwd, buf.data(), buf.size(), &result)};

  if (error_code != 0)
  {
    throw sge::config::exception{
        FCPPT_TEXT("Couldn't determine user name: ") + fcppt::error::strerrno()};
  }

  return fcppt::from_std_string(std::string(pwd.pw_name));
#else
#error "don't know how to find a config path"
#endif
}

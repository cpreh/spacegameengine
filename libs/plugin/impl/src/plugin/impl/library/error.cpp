//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/plugin/impl/library/error.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/format_message.hpp>
#include <awl/backends/windows/windows.hpp>
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <dlfcn.h>
#include <fcppt/config/external_end.hpp>
#else
#error "Implement me!"
#endif

fcppt::string sge::plugin::impl::library::error()
{
#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
  char const *const err(dlerror());

  return err != nullptr ? fcppt::from_std_string(err) : FCPPT_TEXT("no error");
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
  return awl::backends::windows::format_message(::GetLastError());
#endif
}

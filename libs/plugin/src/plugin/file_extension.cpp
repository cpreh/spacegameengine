//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/plugin/file_extension.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>

fcppt::string sge::plugin::file_extension()
{
  return
#ifdef FCPPT_CONFIG_DARWIN_PLATFORM
      FCPPT_TEXT("dylib")
#elifdef FCPPT_CONFIG_POSIX_PLATFORM
      FCPPT_TEXT("so")
#elifdef FCPPT_CONFIG_WINDOWS_PLATFORM
      FCPPT_TEXT("dll")
#else
#error "Don't know which plugin extension to use!"
#endif
          ;
}

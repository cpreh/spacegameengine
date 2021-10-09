//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/added.hpp>
#include <sge/font/exception.hpp>
#include <sge/pango/added.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <fontconfig/fontconfig.h>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::pango::added::added(std::filesystem::path const &_path) : sge::font::added()
{
  // TODO(philipp): Don't use the global fontmap
  if (::FcConfigAppFontAddFile(
          nullptr, fcppt::cast::to_char_ptr<FcChar8 const *>(_path.string().c_str())) != FcTrue)
  {
    throw sge::font::exception{
        FCPPT_TEXT("Unable to add font ") + fcppt::filesystem::path_to_string(_path)};
  }
}

sge::pango::added::~added() // NOLINT(hicpp-use-equals-default,modernize-use-equals-default)
{
  // TODO(philipp): Can we free this custom font?
}

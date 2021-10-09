//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/added.hpp>
#include <sge/font/exception.hpp>
#include <sge/gdifont/added.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::gdifont::added::added(std::filesystem::path const &_path) : path_(_path)
{
  if (AddFontResourceEx(fcppt::filesystem::path_to_string(_path).c_str(), FR_PRIVATE, nullptr) == 0)
    throw sge::font::exception{
        FCPPT_TEXT("Unable to add font ") + fcppt::filesystem::path_to_string(_path)};
}

sge::gdifont::added::~added()
{
  FCPPT_ASSERT_ERROR(
      RemoveFontResourceEx(fcppt::filesystem::path_to_string(path_).c_str(), FR_PRIVATE, nullptr) !=
      0);
}

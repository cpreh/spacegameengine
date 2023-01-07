//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/impl/file_error_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

fcppt::string common_error(std::filesystem::path const &_path)
{
  return FCPPT_TEXT("Error in file ") + fcppt::filesystem::path_to_string(_path) +
         FCPPT_TEXT(" : ");
}

}

fcppt::string sge::parse::impl::file_error_string(
    std::filesystem::path const &_path, std::string &&_error)
{
  return common_error(_path) + fcppt::from_std_string(_error);
}

fcppt::string sge::parse::impl::file_error_string(
    std::filesystem::path const &_path, std::wstring &&_error)
{
  return fcppt::optional::maybe(
      fcppt::from_std_wstring(_error),
      [&_path] { return common_error(_path) + FCPPT_TEXT("Failed to convert error message!"); },
      [&_path](fcppt::string &&_fcppt_error)
      { return common_error(_path) + std::move(_fcppt_error); });
}

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/exception.hpp>
#include <sge/config/impl/try_create_path.hpp>
#include <fcppt/error_code_to_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/use.hpp>
#include <fcppt/either/error_from_optional.hpp>
#include <fcppt/either/no_error.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/create_directories_recursive.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <system_error>
#include <fcppt/config/external_end.hpp>

std::filesystem::path sge::config::impl::try_create_path(std::filesystem::path const &_path)
{
  fcppt::either::no_error const result{fcppt::either::to_exception(
      fcppt::either::error_from_optional(fcppt::filesystem::create_directories_recursive(_path)),
      [&_path](std::error_code const _error)
      {
        return sge::config::exception{
            FCPPT_TEXT("Failed to create ") + fcppt::filesystem::path_to_string(_path) +
            FCPPT_TEXT(". Reason: ") + fcppt::error_code_to_string(_error)};
      })};

  FCPPT_USE(result);

  return _path;
}

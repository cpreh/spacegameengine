//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/impl/parse_file.hpp>
#include <sge/parse/json/file_result.hpp>
#include <sge/parse/json/grammar.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::parse::json::file_result sge::parse::json::parse_file(std::filesystem::path const &_path)
{
  return sge::parse::impl::parse_file(_path, sge::parse::json::grammar{});
}

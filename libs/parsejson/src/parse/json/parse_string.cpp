//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/json/grammar.hpp>
#include <sge/parse/json/parse_string.hpp>
#include <sge/parse/json/string_result.hpp>
#include <fcppt/parse/grammar_parse_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::json::string_result sge::parse::json::parse_string(std::string &&_string)
{
  return fcppt::parse::grammar_parse_string(std::move(_string), sge::parse::json::grammar{});
}

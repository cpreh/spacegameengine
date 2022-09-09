//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/string_to_path.hpp>
#include <fcppt/algorithm/split_string.hpp>

sge::parse::json::path
sge::parse::json::string_to_path(sge::charconv::utf8_string const &_input_path)
{
  return sge::parse::json::path{fcppt::algorithm::split_string(_input_path,'/')};
}

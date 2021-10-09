//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/string_to_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::json::path
sge::parse::json::string_to_path(sge::charconv::utf8_string const &_input_path)
{
  sge::parse::json::path::sequence_type parts{};

  boost::algorithm::split(parts, _input_path, boost::algorithm::is_any_of("/"));

  return sge::parse::json::path(std::move(parts));
}

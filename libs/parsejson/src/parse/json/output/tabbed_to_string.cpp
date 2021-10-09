//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/start_fwd.hpp>
#include <sge/parse/json/output/tabbed_to_stream.hpp>
#include <sge/parse/json/output/tabbed_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>

sge::charconv::utf8_string
sge::parse::json::output::tabbed_to_string(sge::parse::json::start const &_start)
{
  std::ostringstream stream{};

  json::output::tabbed_to_stream(stream, _start);

  return stream.str();
}

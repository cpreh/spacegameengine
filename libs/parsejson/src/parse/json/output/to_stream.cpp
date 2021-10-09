//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/json/start_fwd.hpp>
#include <sge/parse/json/output/tabbed_to_stream.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

void sge::parse::json::output::to_stream(
    std::ostream &_stream, sge::parse::json::start const &_data)
{
  sge::parse::json::output::tabbed_to_stream(_stream, _data);
}

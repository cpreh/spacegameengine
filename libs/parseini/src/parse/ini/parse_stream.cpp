//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/grammar.hpp>
#include <sge/parse/ini/parse_stream.hpp>
#include <sge/parse/ini/stream_result.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::stream_result sge::parse::ini::parse_stream(std::istream &_stream)
{
  return fcppt::parse::grammar_parse_stream(_stream, sge::parse::ini::grammar{});
}

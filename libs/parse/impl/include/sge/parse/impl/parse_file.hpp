//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_IMPL_PARSE_FILE_HPP_INCLUDED
#define SGE_PARSE_IMPL_PARSE_FILE_HPP_INCLUDED

#include <sge/parse/file_result.hpp>
#include <fcppt/string_literal.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/grammar_fwd.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/parse/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::impl
{

template <typename Result, typename Ch, typename Skipper>
sge::parse::file_result<Ch, Result> parse_file(
    std::filesystem::path const &_path, fcppt::parse::grammar<Result, Ch, Skipper> const &_grammar)
{
  return fcppt::optional::maybe(
      fcppt::filesystem::open<std::basic_ifstream<Ch>>(_path, std::ios_base::binary),
      [] {
        return fcppt::either::make_failure<Result>(
            fcppt::optional::object<fcppt::parse::error<Ch>>{});
      },
      [&_grammar, &_path](std::basic_istream<Ch> &&_ifs)
      {
        _ifs.unsetf(std::ios_base::skipws);

        return fcppt::either::map_failure(
            fcppt::parse::grammar_parse_stream(_ifs, _grammar),
            [&_path](fcppt::parse::error<Ch> &&_failure)
            {
              return fcppt::optional::make(fcppt::parse::error<Ch>{
                  FCPPT_STRING_LITERAL(Ch, "Failed to parse \"") + _path.string<Ch>() +
                  FCPPT_STRING_LITERAL(Ch, "\": ") + std::move(_failure.get())});
            });
      });
}

}

#endif

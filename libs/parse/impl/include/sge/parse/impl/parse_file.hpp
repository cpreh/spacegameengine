//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_IMPL_PARSE_FILE_HPP_INCLUDED
#define SGE_PARSE_IMPL_PARSE_FILE_HPP_INCLUDED

#include <sge/parse/file_result.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/string_literal.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/grammar_fwd.hpp>
#include <fcppt/parse/grammar_parse_stream.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/parse/parse_stream_error_output.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <istream>
#include <string>
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
            fcppt::optional::object<std::basic_string<Ch>>{});
      },
      // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
      [&_grammar, &_path](std::basic_istream<Ch> &&_ifs)
      {
        _ifs.unsetf(std::ios_base::skipws);

        return fcppt::either::map_failure(
            fcppt::parse::grammar_parse_stream(_ifs, _grammar),
            // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
            [&_path](fcppt::parse::parse_stream_error<Ch> &&_failure)
            {
              // TODO(philipp): This is a workaround for now. We should use better error types here.
              return fcppt::optional::make(
                  FCPPT_STRING_LITERAL(Ch, "Failed to parse \"") + _path.string<Ch>() +
                  FCPPT_STRING_LITERAL(Ch, "\": ") +
                  fcppt::output_to_string<std::basic_string<Ch>>(_failure));
            });
      });
}

}

#endif

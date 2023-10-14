//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/parse_string.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/parse/parse_string_error.hpp>
#include <fcppt/parse/parse_string_error_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fcppt/config/external_end.hpp>

int main()
{
  return fcppt::either::match(
      sge::parse::ini::parse_string(
          std::string{"[blabla]\nfoo = 42\nconfuse=5\nbar=3.4\nimagepath=/tmp/test\n"
                      "[section2]\nblubb=bar\n"}),
      [](fcppt::parse::parse_string_error<char> const &_error)
      {
        fcppt::io::cerr() << fcppt::from_std_string(fcppt::output_to_std_string(_error))
                          << FCPPT_TEXT('\n');

        return EXIT_FAILURE;
      },
      [](sge::parse::ini::start const &_result)
      {
        sge::parse::ini::output::to_stream(std::cout, _result);

        return EXIT_SUCCESS;
      });
}

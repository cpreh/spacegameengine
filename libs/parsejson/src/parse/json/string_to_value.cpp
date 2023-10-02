//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/exception.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/parse_string.hpp>
#include <sge/parse/json/string_to_value.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/parse/parse_string_error.hpp>
#include <fcppt/parse/parse_string_error_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::json::value sge::parse::json::string_to_value(std::string &&_string)
{
  return sge::parse::json::find_member_value_exn(
             fcppt::make_cref(
                 fcppt::either::to_exception(
                     sge::parse::json::parse_string("{ \"value\" : " + std::move(_string) + " }"),
                     // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
                     [](fcppt::parse::parse_string_error<char> &&_error) {
                       return sge::parse::exception{
                           fcppt::from_std_string(fcppt::output_to_std_string(_error))};
                     })
                     .object()
                     .members),
             "value")
      .get();
}

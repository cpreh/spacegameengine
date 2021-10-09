//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_CONVERT_TO_INT_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_INT_HPP_INCLUDED

#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json::convert
{

template <typename IntType>
IntType to_int(sge::parse::json::value const &_value)
{
  static_assert(std::is_integral_v<IntType>, "IntType must be an integral type");

  return fcppt::optional::to_exception(
      fcppt::cast::truncation_check<IntType>(
          sge::parse::json::get_exn<sge::parse::json::int_type const>(fcppt::make_cref(_value))
              .get()),
      [] { return sge::parse::json::exception{FCPPT_TEXT("convert::to_int: value too large")}; });
}

}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/math/matrix/comparison.hpp>
#include <fcppt/math/matrix/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("parse::json::convert_from", "[sge]")
{
  auto const make_row(
      [](std::vector<int> const &_values) -> sge::parse::json::value
      {
        return sge::parse::json::make_value(
            sge::parse::json::array(fcppt::algorithm::map<sge::parse::json::element_vector>(
                _values,
                [](int const _value)
                {
                  return fcppt::make_recursive(sge::parse::json::make_value(
                      fcppt::cast::size<sge::parse::json::int_type>(_value)));
                })));
      });

  auto const make_matrix(
      [&make_row](std::vector<std::vector<int>> const &_values) -> sge::parse::json::value
      {
        return sge::parse::json::make_value(
            sge::parse::json::array(fcppt::algorithm::map<sge::parse::json::element_vector>(
                _values,
                [&make_row](std::vector<int> const &_inner)
                { return fcppt::make_recursive(make_row(_inner)); })));
      });

  sge::parse::json::value const value(make_matrix({{1, 2}, {3, 4}, {5, 6}}));

  using int_3_2_matrix = fcppt::math::matrix::static_<int, 3, 2>;

  int_3_2_matrix const result(sge::parse::json::convert_from<int_3_2_matrix>(value));

  CHECK(
      result == int_3_2_matrix(
                    fcppt::math::matrix::row(1, 2),
                    fcppt::math::matrix::row(3, 4),
                    fcppt::math::matrix::row(5, 6)));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END

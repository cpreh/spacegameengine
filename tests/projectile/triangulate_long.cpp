//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/math/vector/object.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

namespace
{

using unit = long; // NOLINT(google-runtime-int)

using vector2 = fcppt::math::vector::static_<unit, 2>;

using triangle = fcppt::array::object<vector2, 3>;

using triangle_sequence = std::vector<triangle>;

using point_sequence = std::vector<vector2>;

void test_long(point_sequence const &_points, unit const _epsilon)
{
  triangle_sequence const result(sge::projectile::triangulation::triangulate<
                                 sge::projectile::triangulation::default_tag,
                                 triangle_sequence>(_points, _epsilon));

  CHECK(
      result.size() ==
      _points.size() - 2U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );

  // FIXME
}

}

TEST_CASE("projectile::triangulate_long", "[sge]")
{
  test_long(
      point_sequence{
          vector2(0, 0),
          vector2(
              100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              0),
          vector2(
              100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              100 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          vector2(
              0,
              100 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              )},
      0L);

  test_long(
      point_sequence{
          vector2(0, 0),
          vector2(
              0,
              1000 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          vector2(
              2000, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              2000 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          vector2(
              1000, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              500 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              )},
      0L);
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END

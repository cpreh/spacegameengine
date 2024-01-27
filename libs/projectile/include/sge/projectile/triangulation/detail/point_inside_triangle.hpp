//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_POINT_INSIDE_TRIANGLE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_POINT_INSIDE_TRIANGLE_HPP_INCLUDED

#include <sge/projectile/triangulation/traits/access_element.hpp>
#include <sge/projectile/triangulation/traits/scalar.hpp>
#include <fcppt/array/get.hpp>
#include <fcppt/array/object_impl.hpp>

namespace sge::projectile::triangulation::detail
{

template <typename Tag, typename Vertex>
bool point_inside_triangle(
    fcppt::array::object<Vertex, 3U> const &_triangle, Vertex const &_point)
{
  Vertex const v1{fcppt::array::get<0U>(_triangle)};
  Vertex const v2{fcppt::array::get<1U>(_triangle)};
  Vertex const v3{fcppt::array::get<2U>(_triangle)};

  using access_element = sge::projectile::triangulation::traits::access_element<Vertex, Tag>;

  using scalar = typename sge::projectile::triangulation::traits::scalar<Vertex, Tag>::type;

  scalar const v10(access_element::execute(v1, 0));
  scalar const v11(access_element::execute(v1, 1));
  scalar const v20(access_element::execute(v2, 0));
  scalar const v21(access_element::execute(v2, 1));
  scalar const v30(access_element::execute(v3, 0));
  scalar const v31(access_element::execute(v3, 1));
  scalar const p0(access_element::execute(_point, 0));
  scalar const p1(access_element::execute(_point, 1));
  scalar const ax(v30 - v20);
  scalar const ay(v31 - v21);
  scalar const bx(v10 - v30);
  scalar const by(v11 - v31);
  scalar const cx(v20 - v10);
  scalar const cy(v21 - v11);
  scalar const apx(p0 - v10);
  scalar const apy(p1 - v11);
  scalar const bpx(p0 - v20);
  scalar const bpy(p1 - v21);
  scalar const cpx(p0 - v30);
  scalar const cpy(p1 - v31);
  scalar const a_cross_bp(ax * bpy - ay * bpx);
  scalar const c_cross_ap(cx * apy - cy * apx);
  scalar const b_cross_cp(bx * cpy - by * cpx);
  auto const zero(static_cast<scalar>(0));

  return a_cross_bp >= zero && b_cross_cp >= zero && c_cross_ap >= zero;
}

}

#endif

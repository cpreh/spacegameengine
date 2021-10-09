//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/triangle.hpp>
#include <sge/projectile/impl/object_extrusion_depth.hpp>
#include <sge/projectile/impl/shape/triangle_scalars.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/shape/detail/scalar_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <fcppt/config/external_end.hpp>

sge::projectile::shape::detail::scalar_container sge::projectile::impl::shape::triangle_scalars(
    fcppt::log::object &_log, sge::projectile::shape::triangle_sequence const &_triangles)
{
  sge::projectile::shape::detail::scalar_container scalars(
      _triangles.size() * 8U * 3U *
      3U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );

  FCPPT_LOG_DEBUG(
      _log,
      fcppt::log::out << FCPPT_TEXT("constructing triangle mesh with ") << _triangles.size()
                      << FCPPT_TEXT(" triangles"))

  auto current_scalar{scalars.begin()};

  // TODO(philipp): Find a better way to express this
  for (sge::projectile::triangle const &triangle : _triangles)
  {
    using extrusion_array = fcppt::array::object<btScalar, 2>;

    extrusion_array const extrusion_depth{
        static_cast<btScalar>(-sge::projectile::impl::object_extrusion_depth() / 2),
        static_cast<btScalar>(sge::projectile::impl::object_extrusion_depth() / 2)};

    for (btScalar const current_z : extrusion_depth)
    {
      FCPPT_LOG_VERBOSE(_log, fcppt::log::out << FCPPT_TEXT("triangle begin"))

      for (auto const &current_triangle_point : triangle)
      {
        FCPPT_LOG_VERBOSE(
            _log,
            fcppt::log::out << FCPPT_TEXT("adding point ") << current_triangle_point.x()
                            << FCPPT_TEXT(',') << current_triangle_point.y() << FCPPT_TEXT(',')
                            << current_z)

        *current_scalar++ = current_triangle_point.x();
        *current_scalar++ = current_triangle_point.y();
        *current_scalar++ = current_z;
      }

      FCPPT_LOG_VERBOSE(_log, fcppt::log::out << FCPPT_TEXT("triangle end"))
    }
  }

  return scalars;
}

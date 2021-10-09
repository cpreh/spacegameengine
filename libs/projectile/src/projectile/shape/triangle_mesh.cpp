//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/log.hpp>
#include <sge/projectile/impl/shape/triangle_indices.hpp>
#include <sge/projectile/impl/shape/triangle_scalars.hpp>
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>
#include <fcppt/config/external_end.hpp>

sge::projectile::shape::triangle_mesh::triangle_mesh(
    sge::projectile::log const &_log, sge::projectile::shape::triangle_sequence const &_triangles)
    : scalars_(sge::projectile::impl::shape::triangle_scalars(_log.triangle_log(), _triangles)),
      indices_(sge::projectile::impl::shape::triangle_indices(_log.triangle_log(), _triangles)),
      mesh_(fcppt::make_unique_ptr<btTriangleIndexVertexArray>(
          // number of triangles
          static_cast<int>(
              _triangles.size() *
              8U), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          // pointer to index array
          indices_.data(),
          // index stride
          static_cast<int>(3U * sizeof(int)),
          // number of vertices
          static_cast<int>(
              _triangles.size() * 8U *
              3U), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          // pointer to vertex array
          scalars_.data(),
          // vertex stride
          static_cast<int>(3U * sizeof(btScalar)))),
      bullet_shape_(fcppt::make_unique_ptr<btBvhTriangleMeshShape>(
          mesh_.get_pointer(),
          // use compression (is recommended)
          true))
{
}

btCollisionShape &sge::projectile::shape::triangle_mesh::bullet_shape() { return *bullet_shape_; }

btCollisionShape const &sge::projectile::shape::triangle_mesh::bullet_shape() const
{
  return *bullet_shape_;
}

sge::projectile::shape::triangle_mesh::~triangle_mesh() = default;

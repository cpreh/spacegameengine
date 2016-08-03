/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
	sge::projectile::log const &_log,
	sge::projectile::shape::triangle_sequence const &_triangles
)
:
	scalars_(
		sge::projectile::impl::shape::triangle_scalars(
			_log.triangle_log(),
			_triangles
		)
	),
	indices_(
		sge::projectile::impl::shape::triangle_indices(
			_log.triangle_log(),
			_triangles
		)
	),
	mesh_(
		fcppt::make_unique_ptr<
			btTriangleIndexVertexArray
		>(
			// number of triangles
			static_cast<int>(
				_triangles.size() * 8u),
			// pointer to index array
			indices_.data(),
			// index stride
			static_cast<int>(
				3u *
				sizeof(
					int)),
			// number of vertices
			static_cast<int>(
				_triangles.size() * 8u * 3u),
			// pointer to vertex array
			scalars_.data(),
			// vertex stride
			static_cast<int>(
				3u *
				sizeof(
					btScalar
				)
			)
		)
	),
	bullet_shape_(
		fcppt::make_unique_ptr<
			btBvhTriangleMeshShape
		>(
			mesh_.get_pointer(),
			// use compression (is recommended)
			true
		)
	)
{
}

btCollisionShape &
sge::projectile::shape::triangle_mesh::bullet_shape()
{
	return
		*bullet_shape_;
}

btCollisionShape const &
sge::projectile::shape::triangle_mesh::bullet_shape() const
{
	return
		*bullet_shape_;
}

sge::projectile::shape::triangle_mesh::~triangle_mesh()
{
}

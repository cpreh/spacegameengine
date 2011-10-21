/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../declare_local_logger.hpp"
#include "../object_extrusion_depth.hpp"
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>
#include <fcppt/config/external_end.hpp>


SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("triangle_mesh"))

sge::projectile::shape::triangle_mesh::triangle_mesh(
	triangle_set const &_triangles)
:
	scalars_(
		static_cast<index_vector::size_type>(
			_triangles.size() * 8u * 3u * 3u)),
	indices_(
		// Since we have to extrude each triangle separately (well,
		// technically we don't have to but this is a good compromise)
		// there are 8 output triangles per input triangle.
		static_cast<scalar_vector::size_type>(
			_triangles.size() * 2u * 3u * 4u)),
	mesh_(),
	bullet_shape_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< this
			<< FCPPT_TEXT(": constructing triangle mesh with ")
			<< _triangles.size()
			<< FCPPT_TEXT(" triangles"));

	scalar_vector::iterator current_scalar =
		scalars_.begin();

	for(
		triangle_set::const_iterator triangle_it(
			_triangles.begin()
		);
		triangle_it != _triangles.end();
		++triangle_it
	)
	{
		typedef fcppt::container::array<
			btScalar,
			2
		> extrusion_array;

		extrusion_array const extrusion_depth(
			fcppt::assign::make_array
				(static_cast<btScalar>(-object_extrusion_depth()/2))
				(static_cast<btScalar>(object_extrusion_depth()/2))
		);

		for(
			extrusion_array::const_iterator current_z_it(
				extrusion_depth.begin()
			);
			current_z_it != extrusion_depth.end();
			++current_z_it
		)
		{
			btScalar const current_z(
				*current_z_it
			);

			FCPPT_LOG_VERBOSE(
				local_log,
				fcppt::log::_
					<< this
					<< FCPPT_TEXT(": triangle begin"));

			for(
				triangle::const_iterator triangle_point_it(
					triangle_it->begin()
				);
				triangle_point_it != triangle_it->end();
				++triangle_point_it
			)
			{
				triangle::const_reference current_triangle_point(
					*triangle_point_it
				);

				FCPPT_LOG_VERBOSE(
					local_log,
					fcppt::log::_
						<< this
						<< FCPPT_TEXT(": adding point ")
						<< current_triangle_point[0]
						<< FCPPT_TEXT(',')
						<< current_triangle_point[1]
						<< FCPPT_TEXT(',')
						<< current_z);

				*current_scalar++ = current_triangle_point[0];
				*current_scalar++ = current_triangle_point[1];
				*current_scalar++ = current_z;
			}

			FCPPT_LOG_VERBOSE(
				local_log,
				fcppt::log::_
					<< this
					<< FCPPT_TEXT(": triangle end"));
		}
	}

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< this
			<< FCPPT_TEXT(": filled scalar container, now filling index container"));

	index_vector::iterator current_index_iterator =
		indices_.begin();
	index_vector::value_type current_index =
		0;
	while(current_index_iterator != indices_.end())
	{
		// top
		*current_index_iterator++ = current_index+0;
		*current_index_iterator++ = current_index+1;
		*current_index_iterator++ = current_index+2;
		// bottom
		*current_index_iterator++ = current_index+3;
		*current_index_iterator++ = current_index+4;
		*current_index_iterator++ = current_index+5;

		// first side
		*current_index_iterator++ = current_index+0;
		*current_index_iterator++ = current_index+3;
		*current_index_iterator++ = current_index+4;

		*current_index_iterator++ = current_index+4;
		*current_index_iterator++ = current_index+1;
		*current_index_iterator++ = current_index+0;

		// second side
		*current_index_iterator++ = current_index+5;
		*current_index_iterator++ = current_index+2;
		*current_index_iterator++ = current_index+1;

		*current_index_iterator++ = current_index+1;
		*current_index_iterator++ = current_index+4;
		*current_index_iterator++ = current_index+5;

		// third side side
		*current_index_iterator++ = current_index+3;
		*current_index_iterator++ = current_index+0;
		*current_index_iterator++ = current_index+2;

		*current_index_iterator++ = current_index+2;
		*current_index_iterator++ = current_index+5;
		*current_index_iterator++ = current_index+3;

		current_index += 6;
	}

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< this
			<< FCPPT_TEXT(": filled index container (last index was ") << current_index << FCPPT_TEXT("), now creating bullet shape"));

	mesh_.take(
		fcppt::make_unique_ptr<btTriangleIndexVertexArray>(
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
					btScalar))));

	bullet_shape_.take(
		fcppt::make_unique_ptr<btBvhTriangleMeshShape>(
			mesh_.get(),
			// use compression (is recommended)
			true));
}

btCollisionShape &
sge::projectile::shape::triangle_mesh::bullet_shape()
{
	return *bullet_shape_;
}

btCollisionShape const &
sge::projectile::shape::triangle_mesh::bullet_shape() const
{
	return *bullet_shape_;
}

sge::projectile::shape::triangle_mesh::~triangle_mesh()
{
}

#include "../declare_local_logger.hpp"
#include "../object_extrusion_depth.hpp"
#include <sge/projectile/shape/triangle_mesh.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>

SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("triangle_mesh"))

sge::projectile::shape::triangle_mesh::triangle_mesh(
	triangle_set const &triangles)
:
	scalars_(
		static_cast<index_vector::size_type>(
			triangles.size() * 8u * 3u * 3u)),
	indices_(
		// Since we have to extrude each triangle separately (well,
		// technically we don't have to but this is a good compromise)
		// there are 8 output triangles per input triangle.
		static_cast<scalar_vector::size_type>(
			triangles.size() * 2u * 3u * 4u)),
	mesh_(),
	bullet_shape_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": constructing triangle mesh with ")
			<< triangles.size() 
			<< FCPPT_TEXT(" triangles"));

	scalar_vector::iterator current_scalar = 
		scalars_.begin();
	BOOST_FOREACH(
		triangle_set::const_reference current_triangle,
		triangles)
	{
		BOOST_FOREACH(
			btScalar const current_z,
			fcppt::assign::make_array
				(static_cast<btScalar>(-object_extrusion_depth()/2))
				(static_cast<btScalar>(object_extrusion_depth()/2)).container())
		{
			FCPPT_LOG_VERBOSE(
				local_log,
				fcppt::log::_ 
					<< this
					<< FCPPT_TEXT(": triangle begin"));
			BOOST_FOREACH(
				triangle::const_reference current_triangle_point,
				current_triangle)
			{
				FCPPT_LOG_VERBOSE(
					local_log,
					fcppt::log::_ 
						<< this
						<< FCPPT_TEXT(": adding point ")
						<< current_triangle_point[0] << FCPPT_TEXT(",") << current_triangle_point[1] << FCPPT_TEXT(",") << current_z);

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
				triangles.size() * 8u),
			// pointer to index array
			indices_.data(),
			// index stride
			static_cast<int>(
				3u *
				sizeof(
					int)),
			// number of vertices
			static_cast<int>(
				triangles.size() * 8u * 3u),
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

sge::projectile::shape::triangle_mesh::~triangle_mesh()
{
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

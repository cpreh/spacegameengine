#ifndef SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED

#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/triangle_set.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/LinearMath/btScalar.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>

namespace sge
{
namespace projectile
{
namespace shape
{
class triangle_mesh
:
	public base
{
public:
	explicit
	triangle_mesh(
		triangle_set const &);

	btCollisionShape &
	bullet_shape();

	btCollisionShape const &
	bullet_shape() const;
private:
	typedef
	fcppt::container::raw_vector<int>
	index_vector;

	typedef
	fcppt::container::raw_vector<btScalar>
	scalar_vector;

	scalar_vector scalars_;
	index_vector indices_;
	fcppt::scoped_ptr<btTriangleIndexVertexArray> mesh_;
	fcppt::scoped_ptr<btBvhTriangleMeshShape> bullet_shape_;
};
}
}
}

#endif

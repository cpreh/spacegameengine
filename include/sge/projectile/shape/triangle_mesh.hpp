#ifndef SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/triangle_set.hpp>
#include <sge/projectile/symbol.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

class btCollisionShape;
class btTriangleIndexVertexArray;
class btBvhTriangleMeshShape;

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
FCPPT_NONCOPYABLE(
	triangle_mesh);
public:
	SGE_PROJECTILE_SYMBOL explicit
	triangle_mesh(
		triangle_set const &);

	// No symbol needed here
	btCollisionShape &
	bullet_shape();

	btCollisionShape const &
	bullet_shape() const;

	SGE_PROJECTILE_SYMBOL ~triangle_mesh();
private:
	typedef
	fcppt::container::raw_vector<int>
	index_vector;

	typedef
	fcppt::container::raw_vector<scalar>
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

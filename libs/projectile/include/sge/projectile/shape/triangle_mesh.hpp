//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_TRIANGLE_MESH_HPP_INCLUDED

#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/shape/detail/index_container.hpp>
#include <sge/projectile/shape/detail/scalar_container.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


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
	public sge::projectile::shape::base
{
	FCPPT_NONCOPYABLE(
		triangle_mesh
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	triangle_mesh(
		sge::projectile::log const &,
		sge::projectile::shape::triangle_sequence const &
	);

	// No symbol needed here
	btCollisionShape &
	bullet_shape()
	override;

	btCollisionShape const &
	bullet_shape() const
	override;

	SGE_PROJECTILE_DETAIL_SYMBOL
	~triangle_mesh()
	override;
private:
	sge::projectile::shape::detail::scalar_container scalars_;

	sge::projectile::shape::detail::index_container indices_;

	fcppt::unique_ptr<
		btTriangleIndexVertexArray
	> const mesh_;

	fcppt::unique_ptr<
		btBvhTriangleMeshShape
	> const bullet_shape_;
};

}
}
}

#endif

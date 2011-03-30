#ifndef SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_CIRCLE_HPP_INCLUDED

#include <sge/projectile/symbol.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

class btCollisionShape;

namespace sge
{
namespace projectile
{
namespace shape
{
class SGE_CLASS_SYMBOL circle
:
	public base
{
FCPPT_NONCOPYABLE(
	circle);
public:
	SGE_PROJECTILE_SYMBOL explicit
	circle(
		scalar const radius);

	// No symbol needed here
	btCollisionShape &
	bullet_shape();

	btCollisionShape const &
	bullet_shape() const;

	SGE_PROJECTILE_SYMBOL ~circle();
private:
	fcppt::scoped_ptr<btCollisionShape> bullet_shape_;
};
}
}
}

#endif

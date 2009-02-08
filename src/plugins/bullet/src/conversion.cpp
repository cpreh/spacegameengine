#include "../conversion.hpp"
#include <sge/math/vector/basic_impl.hpp>

sge::bullet::point const sge::bullet::sge_to_bullet(collision::point const &v)
{
	return point(
		static_cast<unit>(v.x()),
		static_cast<unit>(v.y()),
		static_cast<unit>(v.z()));
}

sge::collision::point const sge::bullet::bullet_to_sge(point const &v)
{
	return collision::point(
		static_cast<collision::unit>(v.x()),
		static_cast<collision::unit>(v.y()),
		static_cast<collision::unit>(v.z()));
}

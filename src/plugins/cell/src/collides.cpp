#include "../collides.hpp"
#include "../circle.hpp"
#include <sge/collision/unit.hpp>
#include <sge/math/circle_impl.hpp>

bool
sge::cell::collides(
	circle const &a,
	circle const &b)
{
	typedef math::circle<
		collision::unit
	> circle_type;

	return sge::math::intersects(
		circle_type(
			circle_type::point_type(
				a.center().x(),
				a.center().y()
			),
			a.radius()
		),
		circle_type(
			circle_type::point_type(
				b.center().x(),
				b.center().y()
			),
			b.radius()
		)
	);
}

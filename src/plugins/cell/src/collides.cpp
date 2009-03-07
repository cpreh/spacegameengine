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
			a.center(),
			a.radius()
		),
		circle_type(
			b.center(),
			b.radius()
		)
	);
}

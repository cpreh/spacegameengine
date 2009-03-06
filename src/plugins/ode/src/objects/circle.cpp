#include "../../objects/circle.hpp"
#include "../../space.hpp"
#include "../../world_wrapper.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/structure_cast.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/output.hpp>

sge::ode::objects::circle::circle(
	collision::satellite_ptr _satellite,
	space &space_,
	world_wrapper &world_,
	point const &center,
	point const &speed,
	dReal radius)
:
	body_(
		world_,
		center,
		speed,
		*_satellite
	),
	geom_(
		dCreateSphere(
			space_.id(),
			radius
		),
		body_
	),
	joint_(
		world_,
		body_
	),
	satellite_(
		_satellite
	)
{
	dGeomSetData(geom_.id(),satellite_.get());
}

sge::ode::objects::circle::~circle()
{}

void sge::ode::objects::circle::center(collision::point const &p)
{
	body_.pos(structure_cast<point>(p));
}

sge::collision::point const sge::ode::objects::circle::center() const
{
	return body_.pos();
}

void sge::ode::objects::circle::speed(collision::point const &p)
{
	body_.speed(structure_cast<point>(p));
}

sge::collision::point const sge::ode::objects::circle::speed() const
{
	return body_.speed();
}

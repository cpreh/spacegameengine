#include "../../objects/circle.hpp"

sge::ode::objects::circle::circle(
	sattelite_ptr _sattelite,
	space &space_,
	world &world_,
	point const &center,
	point const &speed,
	dReal radius)
	: body_(world_,center,speed,*_sattelite),
		geom_(dCreateSphere(space_,radius),body_),
		plane_joint_(world_,body_),
		sattelite_(_sattelite)
{
	dGeomSetData(geom_.id(),sattelite_.get());
	dBodySetData(body_.id(),sattelite_.get());
	dBodySetMovedCallback(body_.id(),body::moved);
}

void sge::ode::objects::circle::center(collision::point const &p)
{
	body_.pos(structure_cast<point>(p));
}

collision::point const sge::ode::objects::circle::center() const
{
	return body_.pos();
}

void sge::ode::objects::circle::speed(collision::point const &p)
{
	body_.speed(structure_cast<point>(p));
}

collision::point const sge::ode::objects::circle::speed() const
{
	return body_.speed();
}

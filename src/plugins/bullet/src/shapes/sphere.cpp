#include "../../shapes/sphere.hpp"
#include "../../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("shapes: sphere")));
}


sge::bullet::shapes::sphere::sphere(
	collision::satellite_ptr _satellite,
	collision::constraint::type const _constraint,
	sge::bullet::world &_world,
	unit const _radius,
	collision::solidity::type const _solidity,
	collision::point const &_position)
:
	base(
		bullet_shape_ptr(
			new btSphereShape(
				_radius)),
		_satellite,
		_constraint,
		_world,
		_position,
		_solidity)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Added a sphere with radius: ")
			<< _radius);
}

sge::collision::unit 
sge::bullet::shapes::sphere::radius() const
{
	return 
		dynamic_cast<btSphereShape &>(*shape_).getRadius();
}

void 
sge::bullet::shapes::sphere::radius(
	collision::unit const _radius)
{ 
	// I don't know why it's called "unscaled" radius but it 
	// does the same as the constructor (in bullet-2.75)
	dynamic_cast<btSphereShape &>(*shape_).setUnscaledRadius(
		_radius);
}

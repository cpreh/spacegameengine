#include "../../shapes/circle.hpp"
#include "../../transformer.hpp"

// DEBUG
#include <sge/cerr.hpp>

sge::ode::shapes::circle::circle(
	transformer const &_transformer,
	dSpaceID const _space,
	collision::unit const _radius)
:
	collision::shapes::circle(),
	ode::shapes::base(
		dCreateSphere(
			_space,
			_transformer.unit_to_ode(
				_radius))),
	transformer_(
		_transformer)
{
	//sge::cerr << "created a circle " << this << " with radius " << _radius << "\n";
}

sge::collision::unit sge::ode::shapes::circle::radius() const
{
	return 
		transformer_.unit_from_ode(
			dGeomSphereGetRadius(
				shape_));
}

void sge::ode::shapes::circle::radius(
	collision::unit const _radius)
{
	//sge::cerr << "set radius to " << this << " with radius " << _radius << "\n";
	dGeomSphereSetRadius(
		shape_,
		transformer_.unit_to_ode(
			_radius));
}

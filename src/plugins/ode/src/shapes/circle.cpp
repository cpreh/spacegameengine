#include "../../shapes/sphere.hpp"
#include "../../transformer.hpp"
#include "../../transformer_impl.hpp"

// DEBUG
#include <sge/cerr.hpp>

sge::ode::shapes::sphere::sphere(
	transformer const &_transformer,
	dSpaceID const _space,
	collision::unit const _radius)
:
	collision::shapes::sphere(),
	ode::shapes::base(
		dCreateSphere(
			_space,
			_transformer.unit_to_ode(
				_radius))),
	transformer_(
		_transformer)
{
	//sge::cerr << "created a sphere " << this << " with radius " << _radius << "\n";
}

sge::collision::unit sge::ode::shapes::sphere::radius() const
{
	return 
		transformer_.unit_from_ode(
			dGeomSphereGetRadius(
				shape_));
}

void sge::ode::shapes::sphere::radius(
	collision::unit const _radius)
{
	//sge::cerr << "set radius to " << this << " with radius " << _radius << "\n";
	dGeomSphereSetRadius(
		shape_,
		transformer_.unit_to_ode(
			_radius));
}

#include "../../shapes/circle.hpp"
#include "../../transformer.hpp"
#include "../../transformer_impl.hpp"

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
	dGeomSphereSetRadius(
		shape_,
		transformer_.unit_to_ode(
			_radius));
}

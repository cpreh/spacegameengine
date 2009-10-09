#include "../../shapes/box.hpp"
#include "../../point.hpp"
#include "../../transformer.hpp"
#include "../../transformer_impl.hpp"
#include "../../dim.hpp"
#include <sge/math/dim/basic_impl.hpp>

sge::ode::shapes::box::box(
	transformer const &_transformer,
	dSpaceID const _space,
	collision::dim const &_dim)
:
	collision::shapes::box(),
	ode::shapes::base(
		dCreateBox(
			_space,
			_transformer.dim_to_ode(
				_dim).w(),
			_transformer.dim_to_ode(
				_dim).h(),
			static_cast<dReal>(
				1))),
	transformer_(
		_transformer)
{
	//sge::cerr << "created a box " << this << " with radius " << _radius << "\n";
}

sge::collision::dim const
sge::ode::shapes::box::dim() const
{
	dVector3 result;
	dGeomBoxGetLengths(
		shape_,
		result);
	return 
		transformer_.dim_from_ode(
			sge::ode::dim(
				result[0],
				result[1],
				result[2]));
}

void 
sge::ode::shapes::box::dim(
	collision::dim const &_dim)
{
	//sge::cerr << "set radius to " << this << " with radius " << _radius << "\n";
	sge::ode::dim const o =
		transformer_.dim_to_ode(
			_dim);
	dGeomBoxSetLengths(
		shape_,
		o.w(),
		o.h(),
		o.d());
}

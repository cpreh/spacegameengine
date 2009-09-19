#include "../../shapes/base.hpp"
#include "../../group.hpp"
#include <sge/collision/shape_ambiguity.hpp>

sge::ode::shapes::base::base(
	dGeomID const _shape)
:
	shape_(
		_shape)
{
}

void sge::ode::shapes::base::assign_body(
	dBodyID const _body)
{
	if (dGeomGetBody(shape_))
		throw collision::shape_ambiguity();
	dGeomSetBody(
		shape_,
		_body);
}

void sge::ode::shapes::base::add_to_group(
	group const &_group)
{
	dGeomSetCategoryBits(
		shape_,
		dGeomGetCategoryBits(shape_) | _group.category());
	dGeomSetCollideBits(
		shape_,
		dGeomGetCollideBits(shape_) | _group.collides());
}

sge::ode::shapes::base::~base()
{
	dGeomDestroy(
		shape_);
}
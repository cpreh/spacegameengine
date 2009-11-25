#include "../../shapes/base.hpp"
#include "../../group.hpp"
#include <sge/collision/shape_ambiguity.hpp>

// DEBUG
#include <sge/cerr.hpp>

sge::ode::shapes::base::base(
	dGeomID const _shape)
:
	shape_(
		_shape)
{
	dGeomSetCategoryBits(
		shape_,
		static_cast<group_id>(
			0));
	dGeomSetCollideBits(
		shape_,
		static_cast<group_id>(
			0));
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
	/*sge::cerr
		<< "shape: i should be added to the group with category "
		<< _group.category()
		<< " and collides "
		<< _group.collides()
		<< ", my own category is "
		<< dGeomGetCategoryBits(shape_)
		<< " and my own collides is "
		<< dGeomGetCollideBits(shape_) << "\n";*/
	dGeomSetCategoryBits(
		shape_,
		dGeomGetCategoryBits(shape_) | _group.category());
	dGeomSetCollideBits(
		shape_,
		dGeomGetCollideBits(shape_) | _group.collides());
		/*
	sge::cerr
		<< "shape: aftermath "
		<< ", my own category is "
		<< dGeomGetCategoryBits(shape_)
		<< " and my own collides is "
		<< dGeomGetCollideBits(shape_) << "\n";*/
}

sge::ode::shapes::base::~base()
{
	dGeomDestroy(
		shape_);
}

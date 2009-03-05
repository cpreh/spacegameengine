#include "../body.hpp"
#include "../world_wrapper.hpp"
#include <sge/structure_cast.hpp>
#include <sge/collision/sattelite.hpp>
#include <sge/math/vector/basic_impl.hpp>

sge::ode::body::body(
	world_wrapper &world_,
	point const &center,
	point const &speed,
	collision::sattelite &_sattelite)
	: id_(dBodyCreate(world_.id()))
{
	dBodySetPosition(id(),center.x(),center.y(),center.z());
	dBodySetLinearVel(id(),speed.x(),speed.y(),speed.z());
	dBodySetData(id(),&_sattelite);
	dBodySetMovedCallback(id(),&body::moved);
	dMass m;
	dMassSetSphere(&m,1,0.5);
	dBodySetMass(id(),&m);
}

void sge::ode::body::pos(point const &p)
{
	dBodySetPosition(id(),p.x(),p.y(),p.z());
}

void sge::ode::body::speed(point const &p)
{
	dBodySetLinearVel(id(),p.x(),p.y(),p.z());
}

sge::ode::point const sge::ode::body::pos() const
{
	dReal const * const p = dBodyGetPosition(id());
	return point(p[0],p[1],p[2]);
}

sge::ode::point const sge::ode::body::speed() const
{
	dReal const * const p = dBodyGetLinearVel(id());
	return point(p[0],p[1],p[2]);
}

dBodyID &sge::ode::body::id()
{
	return id_;
}

dBodyID const &sge::ode::body::id() const
{
	return id_;
}

sge::ode::body::~body()
{
	dBodyDestroy(id());
}

void sge::ode::body::moved(dBodyID _id)
{
	dReal const * const p = dBodyGetPosition(_id);
	static_cast<collision::sattelite*>(dBodyGetData(_id))->position_change(
		structure_cast<collision::point>(
			point(p[0],p[1],p[2])));
}

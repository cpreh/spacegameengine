#include "../geom.hpp"
#include "../body.hpp"

sge::ode::geom::geom(
	dGeomID _id,
	body &_body)
	: id_(_id)
{
	dGeomSetBody(id(),_body);
}

dGeomID &sge::ode::geom::id()
{
	return id_;
}

dGeomID const &sge::ode::geom::id() const
{
	return id_;
}

sge::ode::geom::~geom()
{
	dGeomDestroy(id());
}

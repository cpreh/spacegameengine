/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "../body.hpp"
#include "../world_wrapper.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/structure_cast.hpp>

sge::ode::body::body(
	world_wrapper &world_,
	point const &center,
	point const &speed,
	collision::satellite &_satellite)
:
	id_(
		dBodyCreate(
			world_.id()
		)
	)
{
	dBodySetPosition(id(),center.x(),center.y(),center.z());
	dBodySetLinearVel(id(),speed.x(),speed.y(),speed.z());
	dBodySetData(id(),&_satellite);
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

	static_cast<
		collision::satellite*
	>(
		dBodyGetData(
			_id
		)
	)->position_change(
		math::vector::structure_cast<
			collision::point
		>(
			point(
				p[0],
				p[1],
				p[2]
			)
		)
	);
}

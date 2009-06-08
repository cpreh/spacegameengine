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


#include "../../objects/circle.hpp"
#include "../../space.hpp"
#include "../../world_wrapper.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/output.hpp>

sge::ode::objects::circle::circle(
	collision::satellite_ptr _satellite,
	space &space_,
	world_wrapper &world_,
	point const &center,
	point const &speed,
	dReal radius)
:
	body_(
		world_,
		center,
		speed,
		*_satellite
	),
	geom_(
		dCreateSphere(
			space_.id(),
			radius
		),
		body_
	),
	joint_(
		world_,
		body_
	),
	satellite_(
		_satellite
	)
{
	dGeomSetData(geom_.id(),satellite_.get());
}

sge::ode::objects::circle::~circle()
{}

void sge::ode::objects::circle::center(collision::point const &p)
{
	body_.pos(math::vector::structure_cast<point>(p));
}

sge::collision::point const sge::ode::objects::circle::center() const
{
	return body_.pos();
}

void sge::ode::objects::circle::speed(collision::point const &p)
{
	body_.speed(math::vector::structure_cast<point>(p));
}

sge::collision::point const sge::ode::objects::circle::speed() const
{
	return body_.speed();
}

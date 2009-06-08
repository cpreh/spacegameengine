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
#include <sge/collision/satellite.hpp>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>

sge::bullet::objects::circle::circle(
	world &s,
	collision::satellite_ptr sat,
	collision::point const &_center,
	collision::point const &_speed,
	collision::unit const radius)
:
	object(
		s,
		sat,
		shape_ptr(new btSphereShape(radius)),
		static_cast<unit>(1))
{
	center(_center);
	speed(_speed);
}

sge::collision::point const sge::bullet::objects::circle::speed() const
{
	return object::speed();
}

void sge::bullet::objects::circle::speed(sge::collision::point const &n)
{
	object::speed(n);
}

sge::collision::point const sge::bullet::objects::circle::center() const
{
	return object::pos();
}

void sge::bullet::objects::circle::center(sge::collision::point const &n)
{
	object::pos(n);
}

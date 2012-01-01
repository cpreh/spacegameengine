/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/projectile/shape/circle.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::shape::circle::circle(
	scalar const _radius)
:
	base(),
	bullet_shape_(
		fcppt::make_unique_ptr<btSphereShape>(
			_radius))
{
}

btCollisionShape &
sge::projectile::shape::circle::bullet_shape()
{
	return *bullet_shape_;
}

btCollisionShape const &
sge::projectile::shape::circle::bullet_shape() const
{
	return *bullet_shape_;
}

sge::projectile::shape::circle::~circle() {}

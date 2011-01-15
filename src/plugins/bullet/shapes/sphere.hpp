/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_BULLET_SHAPES_SPHERE_HPP_INCLUDED
#define SGE_BULLET_SHAPES_SPHERE_HPP_INCLUDED

#include "base.hpp"
#include "../unit.hpp"
#include "../world_fwd.hpp"
#include <sge/collision/shapes/sphere.hpp>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

namespace sge
{
namespace bullet
{
namespace shapes
{
class sphere
:
	public bullet::shapes::base,
	public collision::shapes::sphere
{
public:
	sphere(
		collision::satellite_ptr,
		collision::constraint::type,
		sge::bullet::world &,
		unit radius,
		collision::solidity::type,
		collision::point const &position);
	
	collision::unit 
	radius() const;
	
	void 
	radius(
		collision::unit);
};
}
}
}

#endif

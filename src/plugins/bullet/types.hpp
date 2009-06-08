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


#ifndef SGE_BULLET_TYPES_HPP_INCLUDED
#define SGE_BULLET_TYPES_HPP_INCLUDED

#include <sge/auto_ptr.hpp>
#include <bullet/BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <bullet/BulletCollision/CollisionShapes/btCollisionShape.h>

namespace sge
{
namespace bullet
{
typedef btDynamicsWorld world_type;
typedef btRigidBody body_type;
typedef btCollisionShape shape_type;
typedef sge::auto_ptr<shape_type> shape_ptr;
typedef btScalar unit;
typedef btVector3 point;

typedef btCollisionConfiguration configuration_type;
typedef btCollisionDispatcher dispatcher_type;
typedef btBroadphaseInterface broadphase_type;
typedef btConstraintSolver constraint_solver_type;
//typedef btOverlapFilterCallback filter_callback_type;
}
}

#endif

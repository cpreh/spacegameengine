/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_BULLET_WORLD_HACK_HPP_INCLUDED
#define SGE_BULLET_WORLD_HACK_HPP_INCLUDED

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

namespace sge
{
namespace bullet
{
/** 
 * Why this hack? 
 *
 * When a new body is created an added to the world, and if that body collides
 * with another body in the world, no "collision begin" is sent until
 * world::stepSimulation is called. This function "stepSimulation", however,
 * might return _without doing anything_. In stepSimulation, bullet checks if
 * enough time has passed since the last time it was called. Only then does it
 * execute the integration functions. This is to prevent glitches with small
 * float values, I think.
 *
 * The problem is, if you add a body to the world, call stepSimulation and then
 * remove the body again, sometimes no begin callback is sent, and no one
 * notices the object is in the world.
 *
 * So we derive from the "real" bullet world and add a function which calls the
 * integration function with a very small timestep so the callbacks are sent.
 */
class world_hack
:
	public btDiscreteDynamicsWorld
{
public:
	world_hack(
		btDispatcher*,
		btBroadphaseInterface*,
		btConstraintSolver*, 
		btCollisionConfiguration*);

	void
	callback_hack();
};
}
}

#endif

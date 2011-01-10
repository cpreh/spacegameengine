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


#include "../system.hpp"
#include "../world.hpp"
#include "../shapes/base.hpp"
#include "../collision_proxy.hpp"
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/assert.hpp>

extern ContactDestroyedCallback gContactDestroyedCallback;
extern ContactProcessedCallback gContactProcessedCallback;
extern ContactAddedCallback gContactAddedCallback;

sge::bullet::system::system()
{
	gContactAddedCallback = &collision_begin;
	//gContactProcessedCallback = &collision_processed;
	gContactDestroyedCallback = &collision_end;
}

sge::collision::world_ptr const
sge::bullet::system::create_world(
	collision::optional_box const &b,
	collision::constraint::type const c)
{
	return 
		fcppt::make_shared_ptr<
			world
		>(
			b,
			c
		);
}

bool 
sge::bullet::system::collision_begin(
	btManifoldPoint& cp,
	btCollisionObject const *o0,
	int,
	int,
	btCollisionObject const *o1,
	int,
	int)
{
	/*
	if (cp.m_lifeTime)
	{
		sge::cerr << "the contact point's lifetime is positive, so it isn't new, doing nothing\n";
		return true;
	}
	*/
	
	shapes::base 
		&s0 = 
			*static_cast<shapes::base *>(
				o0->getUserPointer()),
		&s1 = 
			*static_cast<shapes::base *>(
				o1->getUserPointer());
				
	world &w = 
		s0.world();
		
	FCPPT_ASSERT(
		&w == &(s1.world()));
	
	cp.m_userPersistentData = 
		const_cast<collision_proxy *>(
			&w.collision_begin(
				cp,
				s0,
				s1));
	
	return 
		true;
}

bool
sge::bullet::system::collision_processed(
	btManifoldPoint &,
	void*,
	void*)
{
	//sge::cerr << "collision processed between shape " << body0 << " and " << body1 << "\n";
	return 
		true;
}

bool 
sge::bullet::system::collision_end(
	void * const data)
{
	collision_proxy const &p = 
		*static_cast<collision_proxy const *>(
			data);
			
	p.world().collision_end(
		*p.shapes().first,
		*p.shapes().second);
		
	return 
		true;
}

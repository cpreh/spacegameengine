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


#ifndef SGE_BULLET_BODY_MANAGER_HPP_INCLUDED
#define SGE_BULLET_BODY_MANAGER_HPP_INCLUDED

#include "world_fwd.hpp"
#include "collision_proxy.hpp"
#include <sge/collision/shape_callback.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <map>

class btRigidBody;
class btManifoldPoint;

namespace sge
{
namespace bullet
{
class body_manager
{
public:
	// the body manager has to know the world because collision_proxy gets it
	explicit 
	body_manager(
		world &);
	
	collision_proxy const &
	begin(
		btManifoldPoint &,
		shapes::base &,
		shapes::base &);
	
	void
	end(
		shapes::base &,
		shapes::base &);
	
	fcppt::signal::auto_connection
	register_begin(
		collision::shape_callback const &);
		
	fcppt::signal::auto_connection
	register_end(
		collision::shape_callback const &);
		
	fcppt::signal::auto_connection
	register_solid(
		collision::shape_callback const &);
private:
	typedef 
	unsigned
	size_type;
	
	// no sge::container::map here because it lacks the pair<iterator,bool>::insert method
	typedef
	std::map
	<
		collision_proxy,
		size_type
	>
	pair_map;
	
	fcppt::signal::object<collision::shape_callback_fn> 
		begin_callback_,
		end_callback_,
		solid_callback_;
	world &world_;
	pair_map pairs_;
};
}
}

#endif

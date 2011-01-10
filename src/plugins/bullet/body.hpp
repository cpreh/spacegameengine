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


#ifndef SGE_BULLET_BODY_HPP_INCLUDED
#define SGE_BULLET_BODY_HPP_INCLUDED

#include "point.hpp"
#include "world_fwd.hpp"
#include "shapes/base_fwd.hpp"
#include <sge/collision/satellite_fwd.hpp>
#include <sge/collision/body.hpp>
#include <sge/collision/shapes/container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>

namespace sge
{
namespace bullet
{
class body
:
	public collision::body
{
public:
	body(
		world &,
		collision::shapes::container const &,
		point const &position,
		point const &linear_velocity);
	
	collision::point const 
	position() const;
	
	void 
	position(
		collision::point const &);
		
	/// This is called by the position changer and merely updates the body's position (not the position of its shapes)
	void 
	position_changed(
		collision::point const &);
		
	collision::point const 
	linear_velocity() const;
	
	void 
	linear_velocity(
		collision::point const &);
	
	void 
	add_shape(
		collision::shapes::base_ptr);
	
	// Is called by shapes::bases destructor
	void
	remove_shape(
		shapes::base &);
	
	~body();
private:
	typedef 
	std::vector<shapes::base_ptr> 
	shape_container;
	
	world &world_;
	shape_container shapes_;
	point position_;
	point linear_velocity_;
	unsigned solid_shapes_;
};
}
}

#endif

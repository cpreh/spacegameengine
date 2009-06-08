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


#ifndef SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED

#include "../space_fwd.hpp"
#include "../world_wrapper_fwd.hpp"
#include "../body.hpp"
#include "../geom.hpp"
#include "../plane_joint.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
namespace objects
{
class circle : public collision::objects::circle
{
public:
	circle(
		collision::satellite_ptr,
		space &,
		world_wrapper &,
		point const &center,
		point const &speed,
		dReal radius);

	~circle();

	void center(collision::point const &);
	collision::point const center() const;
	void speed(collision::point const &);
	collision::point const speed() const;
private:
	body body_;
	geom geom_;
	plane_joint joint_;
	collision::satellite_ptr satellite_;
};
}
}
}

#endif

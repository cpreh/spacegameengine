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
#ifndef SGE_BULLET_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_BULLET_OBJECTS_CIRCLE_HPP_INCLUDED

#include <sge/collision/objects/circle.hpp>
#include "../object.hpp"

namespace sge
{
namespace bullet
{
namespace objects
{

class circle : public object, public collision::objects::circle
{
	public:
	circle(
		world &,
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius);
	
	void speed(sge::collision::point const &);
	sge::collision::point const speed() const;
	void center(sge::collision::point const &);
	sge::collision::point const center() const;
};
}
}
}

#endif

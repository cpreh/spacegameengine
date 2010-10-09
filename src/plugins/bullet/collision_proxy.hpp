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


#ifndef SGE_BULLET_COLLISION_PROXY_HPP_INCLUDED
#define SGE_BULLET_COLLISION_PROXY_HPP_INCLUDED

#include "shapes/base_fwd.hpp"
#include "world_fwd.hpp"
#include <utility>

namespace sge
{
namespace bullet
{
class collision_proxy
{
public:
	typedef 
	std::pair
	<
		shapes::base*,
		shapes::base*
	> 
	shape_pair;
	
	collision_proxy(
		shapes::base &,
		shapes::base &,
		world &);
	
	bool 
	operator<(
		collision_proxy const &) const;
	
	shape_pair const &
	shapes() const;
	
	sge::bullet::world &
	world() const;
private:
	shape_pair shapes_;
	sge::bullet::world *world_;
};
}
}

#endif

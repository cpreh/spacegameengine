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


#include "../conversion.hpp"
#include <sge/math/vector/basic_impl.hpp>

sge::bullet::point const sge::bullet::sge_to_bullet(collision::point const &v)
{
	return point(
		static_cast<unit>(v.x()),
		static_cast<unit>(v.y()),
		static_cast<unit>(v.z()));
}

sge::collision::point const sge::bullet::bullet_to_sge(point const &v)
{
	return collision::point(
		static_cast<collision::unit>(v.x()),
		static_cast<collision::unit>(v.y()),
		static_cast<collision::unit>(v.z()));
}

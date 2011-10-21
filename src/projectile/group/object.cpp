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


#include <sge/projectile/world.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object.hpp>


sge::projectile::group::object::object(
	world &_world)
:
	category_(
		_world.next_group_id()),
	collides_(
		// a valid static_cast since id is short! Winning.
		static_cast<id>(
			0))
{
}

sge::projectile::group::object::~object()
{
}

void
sge::projectile::group::object::collides_with(
	object const &other)
{
	collides_ |= other.category_;
}

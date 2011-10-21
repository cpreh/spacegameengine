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
#include <sge/projectile/ghost/scoped.hpp>


sge::projectile::ghost::scoped::scoped(
	world &_world,
	object &_object,
	group::sequence const &_groups)
:
	world_(
		_world),
	object_(
		_object)
{
	world_.add_ghost(
		object_,
		_groups);
}

sge::projectile::ghost::scoped::~scoped()
{
	world_.remove_ghost(
		object_);
}

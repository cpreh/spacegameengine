/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/fragmented.hpp>
#include <sge/texture/manager.hpp>
#include <sge/assert.hpp>

sge::texture::fragmented::fragmented()
:
	man(0)
{}

sge::texture::fragmented::~fragmented()
{}

void
sge::texture::fragmented::return_fragment(
	part const &p)
{
	on_return_fragment(p);

	if(manager())
	{
		SGE_ASSERT(iter);
		manager()->part_freed(
			*iter,
			*this);
	}
}

bool
sge::texture::fragmented::full() const
{
	return free_value() == 0;
}

void
sge::texture::fragmented::manager(
	texture::manager *const nman)
{
	man = nman;
}

sge::texture::manager *
sge::texture::fragmented::manager() const
{
	return man;
}

void
sge::texture::fragmented::container_position(
	detail::container_position const &nit)
{
	iter = nit;
}

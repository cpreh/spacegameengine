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


#include <sge/sprite/compare.hpp>
#include <sge/sprite/object.hpp>
#include <sge/math/compare.hpp>

bool sge::sprite::equal(
	object const &l,
	object const &r)
{
	return l.visible() == r.visible() &&
	       math::compare(l.z(), r.z()) &&
	       l.texture() == r.texture();
}

bool sge::sprite::less(
	object const &l,
	object const &r)
{
	bool const
		lvis = l.visible(),
		rvis = r.visible();

	depth_type const
		lz = l.z(),
		rz = r.z();

	texture::part_ptr const
		ltex = l.texture(),
		rtex = r.texture();

	return lvis == rvis ?
			math::compare(lz, rz) ?
	                	ltex == rtex ?
	                        	     false
		                : ltex < rtex
		       : lz > rz
		: lvis > rvis;
}

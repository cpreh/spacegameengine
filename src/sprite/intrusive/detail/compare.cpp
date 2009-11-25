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


#include <sge/sprite/intrusive/detail/compare.hpp>
#include <sge/sprite/intrusive/object.hpp>
#include <sge/texture/part.hpp>
#include <sge/renderer/texture.hpp>

bool sge::sprite::intrusive::detail::compare(
	object const &l,
	object const &r)
{
	texture::const_part_ptr const
		texa(l.texture()),
		texb(r.texture());

	return !texa || !texb
		? texa == texb
		: (texa->texture() == texb->texture()
		   && l.visible() == r.visible());
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <sge/texture/atlasing/make_inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>


sge::texture::atlasing::inner_rect const
sge::texture::atlasing::make_inner_rect(
	sge::texture::atlasing::outer_rect const &_outer
)
{
	// We can't use box::stretch here because the values are unsigned
	return
		sge::texture::atlasing::inner_rect(
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector(
					_outer.get().pos().x() + 1u,
					_outer.get().pos().y() + 1u
				),
				sge::renderer::lock_rect::dim(
					_outer.get().size().w() - 2u,
					_outer.get().size().h() - 2u
				)
			)
		);
}

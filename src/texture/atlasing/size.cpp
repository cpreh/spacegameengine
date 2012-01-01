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


#include <sge/texture/atlasing/gap.hpp>
#include <sge/texture/atlasing/need.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::renderer::size_type
sge::texture::atlasing::size(
	renderer::size_type const s,
	bool const force_atlasing
)
{
	return
		need(s) || force_atlasing
		?
			s + 2 * gap()
		:
			s;
}

sge::renderer::dim2 const
sge::texture::atlasing::size(
	renderer::dim2 const &dim,
	bool const force_atlasing
)
{
	return
		renderer::dim2(
			size(
				dim.w(),
				force_atlasing
			),
			size(
				dim.h(),
				force_atlasing
			)
		);
}

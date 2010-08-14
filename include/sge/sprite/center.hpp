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


#ifndef SGE_SPRITE_CENTER_HPP_INCLUDED
#define SGE_SPRITE_CENTER_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices
>
typename object<Choices>::point
center(
	object<
		Choices
	> const &spr
)
{
	return
		spr.pos()
		+ spr.size() / 2;
}

template<
	typename Choices
>
void
center(
	object<
		Choices
	> &spr,
	typename object<
		Choices
	>::point const &center_
)
{
	spr.pos(
		center_
		- spr.size() / 2
	);
}

}
}

#endif

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


#ifndef SGE_SPRITE_CENTER_HPP_INCLUDED
#define SGE_SPRITE_CENTER_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
typename
sge::sprite::object<
	Choices
>::vector const
center(
	sge::sprite::object<
		Choices
	> const &_spr
)
{
	return
		_spr.pos()
		+ _spr.size()
		/
		static_cast<
			typename sge::sprite::object<
				Choices
			>::unit
		>(
			2
		);
}

template<
	typename Choices
>
void
center(
	sge::sprite::object<
		Choices
	> &_spr,
	typename sge::sprite::object<
		Choices
	>::vector const &_center
)
{
	_spr.pos(
		_center
		- _spr.size()
		/
		static_cast<
			typename sge::sprite::object<
				Choices
			>::unit
		>(
			2
		)
	);
}

}
}

#endif

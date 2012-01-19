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


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_ROTATION_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_ROTATION_HPP_INCLUDED

#include <sge/sprite/detail/primitives/rotation_base.hpp>
#include <sge/sprite/detail/primitives/rotation_center.hpp>
#include <majutsu/composite.hpp>
#include <fcppt/mpl/append.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	bool CustomCenter
>
struct rotation;

template<
	typename Choices
>
struct rotation<
	Choices,
	true
>
{
	typedef majutsu::composite<
		typename fcppt::mpl::append<
			typename sge::sprite::detail::primitives::rotation_base<
				Choices
			>::type,
			typename sge::sprite::detail::primitives::rotation_center<
				Choices
			>::type
		>::type
	> type;
};

template<
	typename Choices
>
struct rotation<
	Choices,
	false
>
{
	typedef majutsu::composite<
		typename sge::sprite::detail::primitives::rotation_base<
			Choices
		>::type
	> type;
};

}
}
}
}

#endif

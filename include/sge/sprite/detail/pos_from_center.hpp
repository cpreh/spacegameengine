/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_POS_FROM_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_POS_FROM_CENTER_HPP_INCLUDED

#include <sge/sprite/detail/get_size.hpp>
#include <sge/sprite/types/center.hpp>
#include <sge/sprite/types/vector.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Elements
>
inline
sge::sprite::types::vector<
	typename
	Choices::type_choices
> const
pos_from_center(
	Elements const &_elements,
	sge::sprite::types::center<
		typename
		Choices::type_choices
	> const _center
)
{
	return
		_center.get()
		-
		sge::sprite::detail::get_size<
			Choices
		>(
			_elements
		)
		/
		fcppt::literal<
			typename
			Choices::type_choices::unit_type
		>(
			2
		);
}

}
}
}

#endif

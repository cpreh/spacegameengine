/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_SIZE_FROM_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SIZE_FROM_TEXTURE_HPP_INCLUDED

#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/texture.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/texture/part.hpp>
#include <majutsu/get.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


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
sge::sprite::types::dim<
	typename
	Choices::type_choices
>
size_from_texture(
	Elements const &_elements
)
{
	return
		fcppt::math::dim::structure_cast<
			sge::sprite::types::dim<
				typename
				Choices::type_choices
			>,
			fcppt::cast::static_cast_fun
		>(
			sge::sprite::deref_texture(
				majutsu::get<
					sge::sprite::roles::texture0
				>(
					_elements
				)
			).size()
		);
}

}
}
}

#endif

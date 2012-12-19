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


#ifndef SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTOR_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTOR_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/texture/part.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{
namespace detail
{

template<
	template<
		typename
	> class Function,
	typename Level
>
struct texture_level_functor
{
	typedef bool result_type;

	template<
		typename Choices
	>
	static
	result_type
	execute(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	)
	{
		typedef typename sge::sprite::object<
			Choices
		>::texture_type texture_type;

		texture_type const
			left_tex(
				_left. template texture_level<
					Level::value
				>()
			),
			right_tex(
				_right. template texture_level<
					Level::value
				>()
			);

		return
			left_tex
			&&
			right_tex
			?
				Function<
					sge::renderer::texture::planar const *
				>()(
					&left_tex->texture(),
					&right_tex->texture()
				)
			:
				Function<
					bool
				>()(
					static_cast<
						bool
					>(
						left_tex
					),
					static_cast<
						bool
					>(
						right_tex
					)
				)
			;
	}
};

}
}
}
}

#endif

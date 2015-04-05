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


#ifndef SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTOR_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DETAIL_TEXTURE_LEVEL_FUNCTOR_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/maybe.hpp>


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
		typedef
		typename
		sge::sprite::object<
			Choices
		>::texture_type
		texture_type;

		typedef
		typename
		texture_type::value_type element_type;

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

		auto const default_compare(
			[
				&left_tex,
				&right_tex
			]{
				return
					Function<
						bool
					>()(
						left_tex.has_value(),
						right_tex.has_value()
					);
			}
		);

		return
			fcppt::maybe(
				left_tex,
				default_compare,
				[
					&right_tex,
					&default_compare
				](
					element_type const &_left_tex
				)
				{
					return
						fcppt::maybe(
							right_tex,
							default_compare,
							[
								&_left_tex
							](
								element_type const &_right_tex
							)
							{
								return
									Function<
										// TODO: Why is this a pointer?
										sge::renderer::texture::planar const *
									>()(
										&sge::sprite::deref_texture(
											_left_tex.texture()
										),
										&sge::sprite::deref_texture(
											_right_tex.texture()
										)
									);
							}
						);
				}
			);
	}
};

}
}
}
}

#endif

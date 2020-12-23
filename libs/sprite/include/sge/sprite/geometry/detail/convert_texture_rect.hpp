//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_CONVERT_TEXTURE_RECT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_CONVERT_TEXTURE_RECT_HPP_INCLUDED

#include <sge/sprite/types/texture_coordinates.hpp>
#include <fcppt/tuple/element.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices,
	typename Rect
>
sge::sprite::types::texture_coordinates<
	typename
	Choices::type_choices
>
convert_texture_rect(
	Rect const &_rect
)
{
	using
	return_type
	=
	sge::sprite::types::texture_coordinates<
		typename
		Choices::type_choices
	>;

	return
		return_type(
			fcppt::tuple::element<
				0U,
				return_type
			>{
				_rect.left(),
				_rect.top()
			},
			fcppt::tuple::element<
				1U,
				return_type
			>{
				_rect.right(),
				_rect.bottom()
			}
		);
}

}
}
}
}

#endif

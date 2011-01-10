/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_IMPL_HPP_INCLUDED

#include <sge/sprite/detail/fill_tex_coordinates_rect.hpp>
#include <sge/sprite/detail/convert_texture_rect.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_repetition.hpp>
#include <sge/sprite/with_texture_coordinates.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/texture/area_texc.hpp>
#include <sge/texture/part.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_texture_coordinates
		>,
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>
	>,
	void
>::type
fill_tex_coordinates_impl(
	Iterator const &_iterator,
	object<
		Choices
	> const &_sprite
)
{
	detail::fill_tex_coordinates_rect<
		Choices
	>(
		_iterator,
		_sprite.texture_coordinates()
	);
}

template<
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_repetition
		>,
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>
	>,
	void
>::type
fill_tex_coordinates_impl(
	Iterator const &_iterator,
	object<
		Choices
	> const &_sprite
)
{
	detail::fill_tex_coordinates_rect<
		Choices
	>(
		_iterator,
		detail::convert_texture_rect(
			texture::area_texc(
				_sprite.texture(),
				_sprite.repetition()
			)
		)
	);
}

template<
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>,
		boost::mpl::not_<	
			boost::mpl::or_<
				boost::mpl::contains<
					typename Choices::elements,
					sprite::with_repetition
				>,
				boost::mpl::contains<
					typename Choices::elements,
					sprite::with_texture_coordinates
				>
			>
		>
	>,
	void
>::type
fill_tex_coordinates_impl(
	Iterator const &_iterator,
	object<
		Choices
	> const &_sprite
)
{
	detail::fill_tex_coordinates_rect<
		Choices
	>(
		_iterator,
		detail::convert_texture_rect(
			renderer::lock_rect_to_coords<
				typename Choices::type_choices::float_type
			>(
				_sprite.texture()->area(),
				_sprite.texture()->texture()->dim()
			)
		)
	);
}

}
}
}

#endif

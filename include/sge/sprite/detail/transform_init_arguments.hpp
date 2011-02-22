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


#ifndef SGE_SPRITE_DETAIL_TRANSFORM_INIT_ARGUMENTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_TRANSFORM_INIT_ARGUMENTS_HPP_INCLUDED

#include <sge/texture/part.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/texture_dim.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_texture.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Class
>
typename boost::enable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_texture
		>,
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>
	>,
	Class const
>::type
transform_init_arguments(
	Class _object
)
{
	if(
		_object. template get<
			sge::sprite::roles::size
		>()
		== texture_dim<
			typename Choices::type_choices::unit_type
		>()
		&&
		_object. template get<
			sge::sprite::roles::texture
		>()
	)
		_object. template set<
			sge::sprite::roles::size
		>(
			fcppt::math::dim::structure_cast<
				typename dim<
					typename Choices::type_choices::unit_type
				>::type
			>(
				_object. template get<
					sge::sprite::roles::texture
				>()->area().size()
			)
		);
	
	return _object;
}

template<
	typename Choices,
	typename Class
>
typename boost::disable_if<
	boost::mpl::and_<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_texture
		>,
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_dim
		>
	>,
	Class const
>::type
transform_init_arguments(
	Class const &_object
)
{
	return _object;
}

}
}
}

#endif

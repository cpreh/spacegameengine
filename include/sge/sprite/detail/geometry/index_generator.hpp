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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_INDEX_GENERATOR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_INDEX_GENERATOR_HPP_INCLUDED

#include <sge/sprite/detail/geometry/index_array.hpp>
#include <sge/sprite/detail/geometry/index_array_type.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Choices
>
class index_generator
{
	typedef typename sge::sprite::detail::geometry::index_array_type<
		Choices
	>::type index_array_type;

	FCPPT_NONASSIGNABLE(
		index_generator
	);
public:
	index_generator()
	:
		indices_(
			sge::sprite::detail::geometry::index_array<
				Choices
			>::value
		),
		index_(
			0u
		),
		ptr_(
			indices_.begin()
		)
	{
	}

	template<
		typename Type
	>
	Type
	operator()() const
	{
		Type const ret(
			static_cast<
				Type
			>(
				*ptr_++ + index_
			)
		);

		if(
			ptr_ == indices_.end()
		)
		{
			ptr_ = indices_.begin();

			index_ +=
				static_cast<
					typename index_array_type::value_type
				>(
					sge::sprite::detail::geometry::vertices_per_sprite<
						Choices
					>::value
				);
		}

		return ret;
	}
private:
	index_array_type const &indices_;

	mutable typename index_array_type::value_type index_;

	mutable typename index_array_type::const_iterator ptr_;
};

}
}
}
}

#endif

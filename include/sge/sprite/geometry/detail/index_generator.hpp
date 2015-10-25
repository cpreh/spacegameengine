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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_INDEX_GENERATOR_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_INDEX_GENERATOR_HPP_INCLUDED

#include <sge/sprite/geometry/detail/index_array.hpp>
#include <sge/sprite/geometry/detail/index_array_type.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/cast/size.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices
>
class index_generator
{
	typedef
	sge::sprite::geometry::detail::index_array_type<
		Choices
	>
	index_array_type;

	FCPPT_NONASSIGNABLE(
		index_generator
	);
public:
	index_generator()
	:
		indices_(
			sge::sprite::geometry::detail::index_array<
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
	operator()(
		fcppt::tag<
			Type
		>
	) const
	{
		Type const ret(
			fcppt::cast::size<
				Type
			>(
				*ptr_++
				+
				index_
			)
		);

		if(
			ptr_ == indices_.end()
		)
		{
			ptr_ = indices_.begin();

			index_ +=
				fcppt::cast::size<
					typename
					index_array_type::value_type
				>(
					sge::sprite::geometry::detail::vertices_per_sprite<
						Choices
					>::value
				);
		}

		return
			ret;
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

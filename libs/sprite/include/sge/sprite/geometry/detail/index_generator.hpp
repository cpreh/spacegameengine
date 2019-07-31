//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_INDEX_GENERATOR_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_INDEX_GENERATOR_HPP_INCLUDED

#include <sge/sprite/geometry/detail/index_array.hpp>
#include <sge/sprite/geometry/detail/index_array_type.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>
#include <fcppt/reference_impl.hpp>
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
			indices_.get().begin()
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
			ptr_ == indices_.get().end()
		)
		{
			ptr_ = indices_.get().begin();

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
	fcppt::reference<
		index_array_type const
	> indices_;

	mutable typename index_array_type::value_type index_;

	mutable typename index_array_type::const_iterator ptr_;
};

}
}
}
}

#endif

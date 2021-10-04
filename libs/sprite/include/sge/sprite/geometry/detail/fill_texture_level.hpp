//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_HPP_INCLUDED

#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/geometry/detail/fill_texture_level_impl.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/tag_type.hpp>


namespace sge::sprite::geometry::detail
{

template<
	typename Iterator,
	typename Choices
>
class fill_texture_level
{
public:
	using
	object
	=
	sge::sprite::object<
		Choices
	>;

	fill_texture_level(
		Iterator const &_iterator,
		object const &_object
	)
	:
		iterator_(
			_iterator
		),
		object_(
			_object
		)
	{
	}

	template<
		typename Level
	>
	void
	operator()(
		Level const &
	) const
	{
		using
		level
		=
		fcppt::tag_type<
			Level
		>;

		sge::sprite::geometry::detail::fill_texture_level_impl(
			level{},
			iterator_,
			object_.get(),
			sge::sprite::deref_texture(
				object_.get(). template texture_level<
					level::value
				>()
			)
		);
	}
private:
	Iterator iterator_;

	fcppt::reference<
		object const
	> object_;
};

}

#endif

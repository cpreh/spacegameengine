//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_size.hpp>
#include <sge/sprite/detail/vf/texture_point_size.hpp>
#include <fcppt/not.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::geometry::detail
{

template<
	typename Level,
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	sge::sprite::detail::config::has_custom_texture_point_size<
		Choices
	>::value,
	void
>
fill_texture_point_size(
	Level const &,
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	using
	texture_point_size
	=
	fcppt::mpl::list::at<
		typename
		sge::sprite::detail::vf::texture_point_size<
			Choices
		>::type,
		Level
	>;

	(*_iterator). template set<
		texture_point_size
	>(
		typename texture_point_size::packed_type(
			_sprite. template texture_point_size_level<
				Level::value
			>()
		)
	);
}

template<
	typename Level,
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::has_custom_texture_point_size<
			Choices
		>::value
	),
	void
>
fill_texture_point_size(
	Level const &,
	Iterator,
	sge::sprite::object<
		Choices
	> const &
)
{
}

}

#endif

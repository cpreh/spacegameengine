//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_pos.hpp>
#include <sge/sprite/detail/vf/texture_point_pos.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/at.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Level,
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	sge::sprite::detail::config::has_custom_texture_point_pos<
		Choices
	>::value,
	void
>
fill_texture_point_pos(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef
	metal::at<
		typename
		sge::sprite::detail::vf::texture_point_pos<
			Choices
		>::type,
		Level
	>
	texture_point_pos;

	(*_iterator). template set<
		texture_point_pos
	>(
		_sprite. template texture_point_pos_level<
			Level::value
		>()
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
		sge::sprite::detail::config::has_custom_texture_point_pos<
			Choices
		>::value
	),
	void
>
fill_texture_point_pos(
	Iterator,
	sge::sprite::object<
		Choices
	> const &
)
{
}

}
}
}
}

#endif

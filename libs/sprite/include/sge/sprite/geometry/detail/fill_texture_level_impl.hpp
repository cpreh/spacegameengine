//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_IMPL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_IMPL_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/sprite/detail/config/has_texture_point_size.hpp>
#include <sge/sprite/geometry/detail/fill_texture_coordinates.hpp>
#include <sge/sprite/geometry/detail/fill_texture_point.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
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
	sge::sprite::detail::config::has_texture<
		Choices
	>::value,
	void
>
fill_texture_level_impl(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite,
	sge::texture::part const &_texture
)
{
	sge::sprite::geometry::detail::fill_texture_coordinates<
		Level
	>(
		_iterator,
		_sprite,
		_texture
	);
}

template<
	typename Level,
	typename Iterator,
	typename Choices
>
inline
std::enable_if_t<
	sge::sprite::detail::config::has_texture_point_size<
		Choices
	>::value,
	void
>
fill_texture_level_impl(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite,
	sge::texture::part const &
)
{
	sge::sprite::geometry::detail::fill_texture_point<
		Level
	>(
		_iterator,
		_sprite
	);
}

}
}
}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_COORDINATES_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_normal_size.hpp>
#include <sge/sprite/detail/config/has_repetition.hpp>
#include <sge/sprite/detail/config/has_texture_coordinates.hpp>
#include <sge/sprite/geometry/detail/convert_texture_rect.hpp>
#include <sge/sprite/geometry/detail/fill_texture_coordinates_rect.hpp>
#include <sge/texture/area_texc.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/not.hpp>
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
	sge::sprite::detail::config::has_texture_coordinates<
		Choices
	>::value
	&&
	sge::sprite::detail::config::has_normal_size<
		Choices
	>::value,
	void
>
fill_texture_coordinates(
	Iterator const &_iterator,
	sge::sprite::object<
		Choices
	> const &_sprite,
	sge::texture::part const &
)
{
	sge::sprite::geometry::detail::fill_texture_coordinates_rect<
		Level,
		Choices
	>(
		_iterator,
		_sprite. template texture_coordinates_level<
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
	sge::sprite::detail::config::has_repetition<
		Choices
	>::value
	&&
	sge::sprite::detail::config::has_normal_size<
		Choices
	>::value,
	void
>
fill_texture_coordinates(
	Iterator const &_iterator,
	sge::sprite::object<
		Choices
	> const &_sprite,
	sge::texture::part const &_texture
)
{
	sge::sprite::geometry::detail::fill_texture_coordinates_rect<
		Level,
		Choices
	>(
		_iterator,
		sge::sprite::geometry::detail::convert_texture_rect<
			Choices
		>(
			sge::texture::area_texc<
				typename Choices::type_choices::float_type
			>(
				_texture,
				_sprite.repetition()
			)
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
	sge::sprite::detail::config::has_normal_size<
		Choices
	>::value
	&&
	fcppt::not_(
		sge::sprite::detail::config::has_repetition<
			Choices
		>::value
		||
		sge::sprite::detail::config::has_texture_coordinates<
			Choices
		>::value
	),
	void
>
fill_texture_coordinates(
	Iterator const &_iterator,
	sge::sprite::object<
		Choices
	> const &,
	sge::texture::part const &_texture
)
{
	sge::sprite::geometry::detail::fill_texture_coordinates_rect<
		Level,
		Choices
	>(
		_iterator,
		sge::sprite::geometry::detail::convert_texture_rect<
			Choices
		>(
			sge::renderer::lock_rect_to_coords<
				typename Choices::type_choices::float_type
			>(
				_texture.area(),
				_texture.texture().size()
			)
		)
	);
}

}
}
}
}

#endif

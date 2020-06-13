//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_TEXTURE_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/texture_coordinates_fwd.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership_fwd.hpp>
#include <sge/sprite/config/with_texture_fwd.hpp>
#include <sge/sprite/detail/primitives/texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	sge::sprite::texture_level TextureLevels,
	sge::sprite::config::texture_coordinates Coordinates,
	sge::sprite::config::texture_ownership Ownership
>
struct with_texture<
	sge::sprite::config::texture_level_count<
		TextureLevels
	>,
	Coordinates,
	Ownership
>
{
	static_assert(
		TextureLevels >= 1U,
		"with_texture requires at least one texture level"
	);

	using
	texture_levels
	=
	sge::sprite::config::texture_level_count<
		TextureLevels
	>;

	using
	coordinates
	=
	std::integral_constant<
		sge::sprite::config::texture_coordinates,
		Coordinates
	>;

	using
	ownership
	=
	std::integral_constant<
		sge::sprite::config::texture_ownership,
		Ownership
	>;

	template<
		typename Choices
	>
	using
	apply
	=
	sge::sprite::detail::primitives::texture<
		Choices,
		texture_levels,
		Coordinates,
		Ownership
	>;
};

}
}
}

#endif

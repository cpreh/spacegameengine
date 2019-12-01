//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_WITH_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/custom_texture_point_pos_fwd.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership_fwd.hpp>
#include <sge/sprite/config/with_texture_point_size_fwd.hpp>
#include <sge/sprite/detail/primitives/texture_point_pos.hpp>
#include <sge/sprite/detail/primitives/texture_point_size.hpp>
#include <sge/sprite/detail/primitives/texture_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/join.hpp>
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
	bool CustomTexturePoint,
	typename SizeOptions,
	sge::sprite::config::texture_ownership Ownership
>
struct with_texture_point_size<
	sge::sprite::config::texture_level_count<
		TextureLevels
	>,
	sge::sprite::config::custom_texture_point_pos<
		CustomTexturePoint
	>,
	SizeOptions,
	Ownership
>
{
	static_assert(
		TextureLevels >= 1u,
		"TextureLevels must be at least 1"
	);

	static_assert(
		SizeOptions::is_texture_point_size::value,
		"SizeOptions must be a texture point size option"
	);

	typedef sge::sprite::config::texture_level_count<
		TextureLevels
	> texture_levels;

	typedef sge::sprite::config::custom_texture_point_pos<
		CustomTexturePoint
	> point_pos;

	typedef SizeOptions point_size;

	typedef std::integral_constant<
		sge::sprite::config::texture_ownership,
		Ownership
	> ownership;

	template<
		typename Choices
	>
	struct apply
	{
		typedef
		metal::join<
			typename
			sge::sprite::detail::primitives::texture_ptr<
				Choices,
				texture_levels,
				ownership::value
			>::type,
			typename
			sge::sprite::detail::primitives::texture_point_pos<
				Choices,
				texture_levels,
				point_pos
			>::type,
			typename
			sge::sprite::detail::primitives::texture_point_size<
				Choices,
				texture_levels,
				point_size
			>::type
		>
		type;
	};
};

}
}
}

#endif

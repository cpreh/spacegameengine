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
		TextureLevels >= 1u,
		"with_texture requires at least one texture level"
	);

	typedef sge::sprite::config::texture_level_count<
		TextureLevels
	> texture_levels;

	typedef std::integral_constant<
		sge::sprite::config::texture_coordinates,
		Coordinates
	> coordinates;

	typedef std::integral_constant<
		sge::sprite::config::texture_ownership,
		Ownership
	> ownership;

	template<
		typename Choices
	>
	using apply
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

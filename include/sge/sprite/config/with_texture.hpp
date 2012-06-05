/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/with_texture_fwd.hpp>
#include <sge/sprite/detail/primitives/texture.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	sge::sprite::texture_level TextureLevels,
	sge::sprite::config::texture_coordinates::type Coordinates,
	sge::sprite::config::texture_ownership::type Ownership
>
struct with_texture<
	sge::sprite::config::texture_level_count<
		TextureLevels
	>,
	Coordinates,
	Ownership
>
{
	FCPPT_STATIC_ASSERT_STATEMENT(
		TextureLevels >= 1u
	);

	typedef sge::sprite::config::texture_level_count<
		TextureLevels
	> texture_levels;

	static sge::sprite::config::texture_coordinates::type const
	coordinates = Coordinates;

	static sge::sprite::config::texture_ownership::type const
	ownership = Ownership;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename Choices
	>
	struct apply
	:
	sge::sprite::detail::primitives::texture<
		Choices,
		texture_levels,
		Coordinates,
		Ownership
	>
	{
	};

FCPPT_PP_POP_WARNING

};

}
}
}

#endif

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


#ifndef SGE_SPRITE_CONFIG_WITH_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_WITH_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/custom_texture_point_pos_fwd.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/with_texture_point_size_fwd.hpp>
#include <sge/sprite/detail/primitives/texture_point_pos.hpp>
#include <sge/sprite/detail/primitives/texture_point_size.hpp>
#include <sge/sprite/detail/primitives/texture_ptr.hpp>
#include <majutsu/composite.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/mpl/append.hpp>


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
	sge::sprite::config::texture_ownership::type Ownership
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
	FCPPT_STATIC_ASSERT_STATEMENT(
		TextureLevels >= 1u
	);

	FCPPT_STATIC_ASSERT_STATEMENT(
		SizeOptions::is_texture_point_size::value
	);

	typedef sge::sprite::config::texture_level_count<
		TextureLevels
	> texture_levels;

	typedef sge::sprite::config::custom_texture_point_pos<
		CustomTexturePoint
	> point_pos;

	typedef SizeOptions point_size;

	static sge::sprite::config::texture_ownership::type const
	ownership = Ownership;

	template<
		typename Choices
	>
	struct apply
	{
		typedef majutsu::composite<
			typename fcppt::mpl::append<
				typename sge::sprite::detail::primitives::texture_ptr<
					Choices,
					texture_levels,
					ownership
				>::type,
				typename fcppt::mpl::append<
					typename sge::sprite::detail::primitives::texture_point_pos<
						Choices,
						texture_levels,
						point_pos
					>::type,
					typename sge::sprite::detail::primitives::texture_point_size<
						Choices,
						texture_levels,
						point_size
					>::type
				>::type
			>::type
		> type;
	};
};

}
}
}

#endif

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


#ifndef SGE_SPRITE_WITH_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_WITH_TEXTURE_HPP_INCLUDED

#include <sge/sprite/detail/fold_texture_levels.hpp>
#include <sge/sprite/primitives/texture.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

struct with_texture
{
	template<
		typename Choices
	>
	struct apply
	{
		typedef typename Choices::type_choices::texture_levels levels;

		BOOST_STATIC_ASSERT(
			levels::value >= 1
		);

		template<
			typename Level
		>
		struct make_role
		{
			typedef majutsu::role<
				primitives::texture::type,
				roles::texture<
					Level::value
				>
			> type;
		};

		typedef majutsu::composite<
			typename detail::fold_texture_levels<
				make_role<
					boost::mpl::_1
				>,
				levels
			>::type
		> type;
	};
};

}
}

#endif

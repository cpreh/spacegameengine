/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_HPP_INCLUDED

#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_ownership_fwd.hpp>
#include <sge/sprite/detail/primitives/texture_coordinates.hpp>
#include <sge/sprite/detail/primitives/texture_ptr.hpp>
#include <sge/sprite/detail/primitives/texture_repetition.hpp>
#include <fcppt/mpl/append.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_coordinates,
	sge::sprite::config::texture_ownership
>
struct texture;

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture<
	Choices,
	TextureLevels,
	sge::sprite::config::texture_coordinates::custom,
	Ownership
>
{
	typedef
	typename
	fcppt::mpl::append<
		typename sge::sprite::detail::primitives::texture_ptr<
			Choices,
			TextureLevels,
			Ownership
		>::type,
		typename sge::sprite::detail::primitives::texture_coordinates<
			Choices,
			TextureLevels
		>::type
	>::type
	type;
};

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture<
	Choices,
	TextureLevels,
	sge::sprite::config::texture_coordinates::repetition,
	Ownership
>
{
	typedef
	typename
	fcppt::mpl::append<
		typename sge::sprite::detail::primitives::texture_ptr<
			Choices,
			TextureLevels,
			Ownership
		>::type,
		typename sge::sprite::detail::primitives::texture_repetition<
			Choices
		>::type
	>::type
	type;
};

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture<
	Choices,
	TextureLevels,
	sge::sprite::config::texture_coordinates::automatic,
	Ownership
>
{
	typedef
	typename
	sge::sprite::detail::primitives::texture_ptr<
		Choices,
		TextureLevels,
		Ownership
	>::type
	type;
};

}
}
}
}

#endif

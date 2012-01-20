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


#ifndef SGE_SPRITE_COMPARE_DETAIL_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DETAIL_TEXTURES_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/compare/texture_level_equal.hpp>
#include <sge/sprite/compare/texture_level_less.hpp>
#include <sge/sprite/config/texture_level_count.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{
namespace detail
{

template<
	sge::sprite::texture_level Level
>
struct textures
{
	template<
		typename Choices
	>
	static
	bool
	execute(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	)
	{
		typedef sge::sprite::config::texture_level_count<
			Level - 1u
		> current_level;

		return
			!sge::sprite::compare::texture_level_equal<
				current_level
			>(
				_left,
				_right
			)
			?
				sge::sprite::compare::texture_level_less<
					current_level
				>(
					_left,
					_right
				)
			:
				sge::sprite::compare::detail::textures<
					Level - 1u
				>::execute(
					_left,
					_right
				)
			;
	}
};

template<>
struct textures<
	0u
>
{
	template<
		typename Choices
	>
	static
	bool
	execute(
		sge::sprite::object<
			Choices
		> const &,
		sge::sprite::object<
			Choices
		> const &
	)
	{
		return false;
	}
};

}
}
}
}

#endif

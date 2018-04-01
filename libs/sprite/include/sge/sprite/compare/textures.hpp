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


#ifndef SGE_SPRITE_COMPARE_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_TEXTURES_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/detail/textures.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{

struct textures
{
	template<
		typename Choices
	>
	using
	is_trivial
	=
	std::false_type;

	typedef
	bool
	result_type;

	template<
		typename Choices
	>
	inline
	std::enable_if_t<
		sge::sprite::detail::config::has_texture<
			Choices
		>::value,
		result_type
	>
	operator()(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	) const
	{
		return
			sge::sprite::compare::detail::textures<
				sge::sprite::detail::config::texture_levels<
					Choices
				>::type::value
			>::execute(
				_left,
				_right
			);
	}
};

}
}
}

#endif

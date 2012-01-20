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


#ifndef SGE_SPRITE_COMPARE_TEXTURE_LEVEL_EQUAL_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_TEXTURE_LEVEL_EQUAL_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{

template<
	typename Level,
	typename Choices
>
typename boost::enable_if<
	sge::sprite::detail::config::has_texture<
		Choices
	>,
	bool
>::type
texture_level_equal(
	sge::sprite::object<
		Choices
	> const &_left,
	sge::sprite::object<
		Choices
	> const &_right
)
{
	sge::texture::const_part_ptr const
		left_tex(
			_left. template texture_level<
				Level::value
			>()
		),
		right_tex(
			_right. template texture_level<
				Level::value
			>()
		);

	return
		left_tex
		&&
		right_tex
		?
			left_tex->texture()
			==
			right_tex->texture()
		:
			left_tex
			==
			right_tex
		;
}

}
}
}

#endif

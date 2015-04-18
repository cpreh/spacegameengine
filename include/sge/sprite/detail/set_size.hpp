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


#ifndef SGE_SPRITE_DETAIL_SET_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SET_SIZE_HPP_INCLUDED

#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/sprite/types/size_or_texture_size.hpp>
#include <majutsu/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Elements
>
inline
typename
std::enable_if<
	Choices::size_choice::texture_option::value
	==
	sge::sprite::config::texture_size_option::never
	,
	void
>::type
set_size(
	Elements &_elements,
	sge::sprite::types::dim<
		typename
		Choices::type_choices
	> const _size

)
{
	majutsu::set<
		sge::sprite::roles::size
	>(
		_elements,
		_size
	);
}

template<
	typename Choices,
	typename Elements
>
inline
typename
std::enable_if<
	Choices::size_choice::texture_option::value
	==
	sge::sprite::config::texture_size_option::maybe
	,
	void
>::type
set_size(
	Elements &_elements,
	sge::sprite::types::dim<
		typename
		Choices::type_choices
	> const _size
)
{
	majutsu::set<
		sge::sprite::roles::size_or_texture_size
	>(
		_elements,
		sge::sprite::types::size_or_texture_size<
			typename
			Choices::type_choices
		>(
			_size
		)
	);
}

}
}
}

#endif

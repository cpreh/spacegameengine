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


#ifndef SGE_SPRITE_DETAIL_SET_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SET_POS_HPP_INCLUDED

#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/pos_or_center.hpp>
#include <sge/sprite/types/pos.hpp>
#include <sge/sprite/types/pos_or_center.hpp>
#include <fcppt/record/set.hpp>
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
	Choices::pos_choice::option::value
	==
	sge::sprite::config::pos_option::pos
	,
	void
>::type
set_pos(
	Elements &_elements,
	sge::sprite::types::pos<
		typename
		Choices::type_choices
	> const _pos

)
{
	fcppt::record::set<
		sge::sprite::roles::pos
	>(
		_elements,
		_pos.get()
	);
}

template<
	typename Choices,
	typename Elements
>
inline
typename
std::enable_if<
	Choices::pos_choice::option::value
	==
	sge::sprite::config::pos_option::pos_or_center
	,
	void
>::type
set_pos(
	Elements &_elements,
	sge::sprite::types::pos<
		typename
		Choices::type_choices
	> const _pos
)
{
	fcppt::record::set<
		sge::sprite::roles::pos_or_center
	>(
		_elements,
		sge::sprite::types::pos_or_center<
			typename
			Choices::type_choices
		>(
			_pos
		)
	);
}

}
}
}

#endif

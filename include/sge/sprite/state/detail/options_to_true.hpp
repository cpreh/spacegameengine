/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_TO_TRUE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_TO_TRUE_HPP_INCLUDED

#include <sge/sprite/state/detail/one_option_to_true.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/mpl/for_each.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
typename
sge::sprite::state::detail::options_class<
	StateChoices
>::type
options_to_true()
{
	typename
	sge::sprite::state::detail::options_class<
		StateChoices
	>::type result{
		fcppt::no_init()
	};

	fcppt::mpl::for_each<
		typename
		StateChoices::optional_elements
	>(
		sge::sprite::state::detail::one_option_to_true<
			StateChoices
		>(
			result
		)
	);

	return result;
}

}
}
}
}

#endif

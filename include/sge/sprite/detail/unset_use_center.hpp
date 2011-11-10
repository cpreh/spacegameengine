/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_UNSET_USE_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_UNSET_USE_CENTER_HPP_INCLUDED

#include <sge/sprite/parameters_fwd.hpp>
#include <sge/sprite/detail/needs_use_center.hpp>
#include <sge/sprite/detail/roles/use_center.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
typename boost::enable_if<
	detail::needs_use_center<
		Choices
	>,
	sprite::parameters<
		Choices
	> &
>::type
unset_use_center(
	sprite::parameters<
		Choices
	> &_param
)
{
	return
		_param
		. template set<
			detail::roles::use_center
		>(
			false
		);
}

template<
	typename Choices
>
typename boost::disable_if<
	detail::needs_use_center<
		Choices
	>,
	sprite::parameters<
		Choices
	> &
>::type
unset_use_center(
	sprite::parameters<
		Choices
	> &_param
)
{
	return
		_param;
}

}
}
}

#endif

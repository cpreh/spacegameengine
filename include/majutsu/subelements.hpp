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


#ifndef MAJUTSU_SUBELEMENTS_HPP_INCLUDED
#define MAJUTSU_SUBELEMENTS_HPP_INCLUDED

#include <majutsu/detail/copy_subelements.hpp>
#include <majutsu/is_role.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>

namespace majutsu
{

template<
	typename Dest,
	typename Src
>
Dest const
subelements(
	Src const &_src
)
{
	Dest ret;

	boost::mpl::for_each<
		typename boost::mpl::remove_if<
			typename Src::memory_type::types,
			boost::mpl::not_<
				majutsu::is_role<
					boost::mpl::_1
				>
			>
		>::type
	>(
		detail::copy_subelements<
			Dest,
			Src
		>(
			ret,
			_src
		)
	);

	return ret;
}

}

#endif

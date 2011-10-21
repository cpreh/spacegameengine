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


#ifndef MAJUTSU_EXTRACT_CONSTANT_HPP_INCLUDED
#define MAJUTSU_EXTRACT_CONSTANT_HPP_INCLUDED

#include <majutsu/flatten.hpp>
#include <majutsu/detail/find_role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/integral_c.hpp>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{

template<
	typename Types,
	typename Role
>
struct extract_constant
{
private:
	typedef typename flatten<
		Types
	>::type flattened_types;

	typedef typename boost::mpl::deref<
		typename detail::find_role<
			flattened_types,
			Role
		>::type
	>::type found_role;
public:
	typedef boost::mpl::integral_c<
		typename found_role::type,
		found_role::value
	> type;
};

}

#endif

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef MAJUTSU_BIND_HPP_INCLUDED
#define MAJUTSU_BIND_HPP_INCLUDED

#include <majutsu/placeholder.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

namespace majutsu
{

template<
	typename Base,
	typename Binders
>
struct bind {
	typedef typename boost::mpl::transform<
		typename Base::type,
		typename Binders::type,
		boost::mpl::if_<
			boost::is_same<
				boost::mpl::_2,
				placeholder
			>,
			boost::mpl::_1,
			boost::mpl::_2
		>
	>::type type;
};

}

#endif

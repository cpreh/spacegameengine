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


#ifndef MAJUTSU_FLATTEN_HPP_INCLUDED
#define MAJUTSU_FLATTEN_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{

template<
	typename Type,
	typename Enable = void
>
struct flatten;

template<
	typename Type
>
struct flatten<
	Type,
	typename boost::enable_if<
		boost::mpl::is_sequence<
			typename Type::type
		>
	>::type
>
{
	typedef typename boost::mpl::fold<
		typename Type::type,
		boost::mpl::vector0<>,
		boost::mpl::copy<
			flatten<
				boost::mpl::_2
			>,
			boost::mpl::back_inserter<
				boost::mpl::_1
			>
		>
	>::type type;
};

template<
	typename Type
>
struct flatten<
	Type,
	typename boost::disable_if<
		boost::mpl::is_sequence<
			typename Type::type
		>
	>::type
>
{
	typedef boost::mpl::vector1<
		Type
	> type;
};

}

#endif

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TYPESWITCH_HPP_INCLUDED
#define SGE_TYPESWITCH_HPP_INCLUDED

#include <limits>
#include <boost/mpl/list.hpp>
#include <boost/mpl/find_if.hpp>

namespace sge
{
template<typename T> struct type_bits {
	enum { value = std::numeric_limits<T>::is_signed
		? std::numeric_limits<T>::digits + 1
		: std::numeric_limits<T>::digits };
};

template<unsigned Bits> struct has_bits {
	template<typename Param>
		struct apply : public boost::mpl::bool_<type_bits<Param>::value == Bits> {};
};

template<typename TList, unsigned Bits> struct typeswitch
	: boost::mpl::deref<typename boost::mpl::find_if<TList, has_bits<Bits> >::type>
{};

typedef boost::mpl::list<char, short, int, long> signed_types;
typedef boost::mpl::list<unsigned char, unsigned short, unsigned, unsigned long> unsigned_types;

typedef typeswitch<signed_types, 8>::type int8;
typedef typeswitch<signed_types,16>::type int16;
typedef typeswitch<signed_types,32>::type int32;

typedef typeswitch<unsigned_types, 8>::type uint8;
typedef typeswitch<unsigned_types,16>::type uint16;
typedef typeswitch<unsigned_types,32>::type uint32;

}

#endif

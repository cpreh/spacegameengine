/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONTAINER_MAP_IMPL_HPP_INCLUDED
#define SGE_CONTAINER_MAP_IMPL_HPP_INCLUDED

#include "map_decl.hpp"
#include "insert_failed.hpp"
#include "not_found.hpp"
#include "../text.hpp"
#include <utility>

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::map()
{}

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::map(
	internal_type const &impl_)
:
	impl_(impl_)
{}

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
template<
	typename In
>
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::map(
	In const beg,
	In const end)
:
	impl_(
		beg,
		end)
{}

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
void sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::insert(
	key_type const &k,
	mapped_type const &m)
{
	if(!impl_.insert(
		std::make_pair(
			k,
			m)).second
	)
		throw insert_failed(
			SGE_TEXT("insert in map failed!"));
}

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
void sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::erase(
	key_type const &k)
{
	if(!impl_.erase(
		k)
	)
		throw not_found(
			SGE_TEXT("erase from map failed!"));
}

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
typename sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::mapped_type const &
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::operator[](
	key_type const &k) const
{
	typename internal_type::const_iterator const it(
		impl_.find(k));
	
	if(it == impl_.end())
		throw not_found(
			SGE_TEXT("operator[] of map failed!"));
	
	return it->second;
}

template<
	template<
		typename,
		typename,
		typename,
		typename
	> class MapType,
	typename Key,
	typename Mapped,
	template<
		typename
	> class Alloc,
	template<
		typename
	> class Comp
>
typename sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::mapped_type &
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::operator[](
	key_type const &k)
{
	return const_cast<
		key_type &
	>(
		const_cast<
			map const &
		>(
			*this)
				[k]);
}

#endif

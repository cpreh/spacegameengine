/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/container/map_decl.hpp>
#include <sge/container/insert_failed.hpp>
#include <sge/container/not_found.hpp>
#include <sge/text.hpp>
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
	insert(
		std::make_pair(
			k,
			m
		)
	);
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
>::insert(
	value_type const &v)
{
	if(!impl_.insert(v).second)
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
>::iterator
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::find(
	key_type const &k)
{
	return impl_.find(k);
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
>::const_iterator
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::find(
	key_type const &k) const
{
	return impl_.find(k);
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
		mapped_type &
	>(
		const_cast<
			map const &
		>(
			*this)
				[k]);
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
bool
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::contains(
	key_type const &key) const
{
	return impl_.find(key) != impl_.end();
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
>::iterator
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::begin()
{
	return impl_.begin();
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
>::const_iterator
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::begin() const
{
	return impl_.begin();
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
>::iterator
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::end()
{
	return impl_.end();
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
>::const_iterator
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::end() const
{
	return impl_.end();
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
>::size_type
sge::container::map<
	MapType,
	Key,
	Mapped,
	Alloc,
	Comp
>::size() const
{
	return impl_.size();
}

#endif

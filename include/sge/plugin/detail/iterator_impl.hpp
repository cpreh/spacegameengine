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



#ifndef SGE_PLUGIN_DETAIL_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_DETAIL_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/plugin/iterator.hpp>

template<typename T>
sge::plugin::iterator<T>::iterator(
	category_array::iterator const it)
:
	it(it)
{}

template<typename T>
void sge::plugin::iterator<T>::advance(const difference_type diff)
{
	it+=diff;
}

template<typename T>
void sge::plugin::iterator<T>::increment()
{
	++it;
}

template<typename T>
void sge::plugin::iterator<T>::decrement()
{
	--it;
}

template<typename T>
bool sge::plugin::iterator<T>::equal(const iterator& r) const
{
	return it == r.it;
}

template<typename T>
typename sge::plugin::iterator<T>::reference
sge::plugin::iterator<T>::dereference() const
{
	return context<T>(**it);
}

template<typename T>
typename sge::plugin::iterator<T>::difference_type
sge::plugin::iterator<T>::distance_to(
	iterator const &r) const
{
	return r.it - it;
}

#endif

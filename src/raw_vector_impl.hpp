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


#ifndef SGE_RAW_VECTOR_IMPL_HPP_INCLUDED
#define SGE_RAW_VECTOR_IMPL_HPP_INCLUDED

#include "raw_vector.hpp"

template<typename T, typename A>
typename sge::raw_vector<T, A>::iterator sge::raw_vector<T, A>::begin()
{
	return first;
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_iterator sge::raw_vector<T, A>::begin() const
{
	return first;
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::iterator sge::raw_vector<T, A>::end()
{
	return last;
}
	
template<typename T, typename A>
typename sge::raw_vector<T, A>::const_iterator sge::raw_vector<T, A>::end() const
{
	return last;
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::reverse_iterator sge::raw_vector<T, A>::rbegin()
{
	return reverse_iterator(last);
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_reverse_iterator sge::raw_vector<T, A>::rbegin() const
{
	return const_reverse_iterator(last);
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::reverse_iterator sge::raw_vector<T, A>::rend()
{
	return reverse_iterator(first);
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_reverse_iterator sge::raw_vector<T, A>::rend() const
{
	return const_reverse_iterator(first);
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::reference sge::raw_vector<T, A>::operator[] (const size_type n)
{
	return *(begin() + n);
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_reference sge::raw_vector<T, A>::operator[] (const size_type n) const
{
	return *(begin() + n);
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::reference sge::raw_vector<T, A>::at(const size_type n)
{
	range_check(n);
	return (*this)[n];
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_reference sge::raw_vector<T, A>::at(const size_type n) const
{
	range_check(n);
	return (*this)[n];
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::reference sge::raw_vector<T, A>::front()
{
	return *begin();
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_reference sge::raw_vector<T, A>::front() const
{
	return *begin();
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::reference sge::raw_vector<T, A>::back()
{
	return *--end();
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_reference sge::raw_vector<T, A>::back() const
{
	return *--end();
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::pointer sge::raw_vector<T, A>::data()
{
	return first;
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::const_pointer sge::raw_vector<T, A>::data() const
{
	return first;
}

template<typename T, typename A>
sge::raw_vector<T, A>::raw_vector(const A& a)
: a(a),
  first(0),
  last(0),
  cap(0)
{}

template<typename T, typename A>
sge::raw_vector<T, A>::raw_vector(const size_type sz, const A& a_)
: a(a_),
  first(a.allocate(sz)),
  last(first + sz),
  cap(last)
{}

template<typename T, typename A>
sge::raw_vector<T, A>::raw_vector(const size_type sz, const T& t, const A& a_)
: a(a_),
  first(a.allocate(sz)),
  last(first + sz),
  cap(last)
{
	for(iterator it = begin(); it != end(); ++it)
		*it = t;
}

template<typename T, typename A>
template<typename In>
sge::raw_vector<T, A>::raw_vector(const In beg, const In end, const A& a)
: a(a)
{
	const difference_type len = std::distance(beg, end);
	resize(len);
	copy(beg, end, begin());
}
	
template<typename T, typename A>
sge::raw_vector<T, A>::raw_vector(const raw_vector& x)
: a(x.a),
  first(a.allocate(x.size())),
  last(first + x.size()),
  cap(last)
{
	copy(x.begin(), x.end(), begin());
}

template<typename T, typename A>
sge::raw_vector<T, A>::~raw_vector()
{
	a.deallocate(first, capacity());
}

template<typename T, typename A>
sge::raw_vector<T, A>& sge::raw_vector<T, A>::operator= (const raw_vector& x)
{
	if(&x == this)
		return;
	assign(x.begin(), x.end());
}

template<typename T, typename A>
template<typename In>
void sge::raw_vector<T, A>::assign(const In beg, const In end)
{
	const difference_type len = std::distance(beg, end);
	resize(len);
	copy(beg, end, begin());
}

template<typename T, typename A>
void sge::raw_vector<T, A>::assign(const size_type n, const T& value)
{
	resize(n);
	std::uninitialized_fill_n(first, n, value);
}

template<typename T, typename A>
void sge::raw_vector<T, A>::push_back(const T& x)
{
	insert(end(), x);
}

template<typename T, typename A>
void sge::raw_vector<T, A>::pop_back()
{
	erase(--end());
}

template<typename T, typename A>
void sge::raw_vector<T, A>::clear()
{
	erase(begin(), end());
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::size_type sge::raw_vector<T, A>::size() const
{
	return last - first;
}

template<typename T, typename A>
bool sge::raw_vector<T, A>::empty() const
{
	return size() == 0;
}

template<typename T, typename A>
typename sge::raw_vector<T, A>::size_type sge::raw_vector<T, A>::max_size() const
{
	return a.max_size();
}

template<typename T, typename A>
void sge::raw_vector<T, A>::swap(raw_vector& x)
{
	std::swap(first, x.first);
	std::swap(last, x.last);
	std::swap(cap, x.cap);
}

template<typename T, typename A>
void sge::raw_vector<T, A>::resize(const size_type sz)
{
	_grow(sz);
}

template <typename T, typename A>
typename sge::raw_vector<T, A>::allocator_type sge::raw_vector<T, A>::get_allocator() const
{
	return a;
}

#endif

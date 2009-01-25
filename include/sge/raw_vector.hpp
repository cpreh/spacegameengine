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


#ifndef SGE_RAW_VECTOR_HPP_INCLUDED
#define SGE_RAW_VECTOR_HPP_INCLUDED

#include "config.h"
#include "raw_vector_fwd.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <iterator>

namespace sge
{

template<
	typename T,
	typename A
>
class raw_vector {
	BOOST_STATIC_ASSERT(boost::is_pod<T>::value);
public:
	typedef T                                     value_type;
	typedef A                                     allocator_type;
	typedef typename A::size_type                 size_type;
	typedef typename A::difference_type           difference_type;
	typedef typename A::pointer                   pointer;
	typedef typename A::const_pointer             const_pointer;
	typedef typename A::reference                 reference;
	typedef typename A::const_reference           const_reference;
	typedef pointer                               iterator;
	typedef const_pointer                         const_iterator;
	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;
	reference at(size_type n);
	const_reference at(size_type n) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	pointer data();
	const_pointer data() const;

	explicit raw_vector(const A& a = A());
	explicit raw_vector(size_type sz, const A& a = A()); // uninitialized vector
	raw_vector(size_type sz, const T& t, const A& a = A());

	template <typename In>
	raw_vector (In beg, In end, const A& a = A());

	raw_vector (const raw_vector& x);
	~raw_vector();

	raw_vector& operator= (const raw_vector& x);
	
	template <typename In>
	void assign (In beg, In end);
	void assign (size_type n, const T& value);

	void push_back (const T& x);
	void pop_back();
	void clear();
		
	size_type size() const;
	bool empty() const;
	size_type max_size() const;
	size_type capacity() const;

	void swap (raw_vector& x);
	void resize_uninitialized(size_type sz);
	void resize(size_type sz, const T& value = T());
	void reserve(size_type sz);

	allocator_type get_allocator() const;

	iterator insert(iterator position, const T& x);
	void insert(iterator position, size_type n, const T& x);
	template <typename In>
	void insert(iterator position, In first, In last);

	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);
private:
	void range_check(size_type n) const;
	size_type new_capacity(size_type new_size) const;
	void set_pointers(pointer src, size_type sz, size_type cap);
	void deallocate();

	struct impl {
		impl(const A&);
		impl(const A&, size_type);

		A a;
		pointer first,
	        	last,
		        cap;
	};

	impl i;
};

template <typename T, typename A>
bool operator==(const raw_vector<T, A>& x, const raw_vector<T,A>& y);

template <typename T, typename A>
bool operator< (const raw_vector<T, A>& x, const raw_vector<T, A>& y);

template <typename T, typename A>
bool operator!=(const raw_vector<T, A>& x, const raw_vector<T, A>& y);

template <typename T, typename A>
bool operator> (const raw_vector<T, A>& x, const raw_vector<T, A>& y);

template <typename T, typename A>
bool operator>=(const raw_vector<T, A>& x, const raw_vector<T, A>& y);

template <typename T, typename A>
bool operator<=(const raw_vector<T, A>& x, const raw_vector<T, A>& y);

template <typename T, typename A>
void swap(raw_vector<T, A>& x, raw_vector<T, A>& y);


}

#endif

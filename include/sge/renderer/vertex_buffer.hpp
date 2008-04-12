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


#ifndef SGE_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_VERTEX_BUFFER_HPP_INCLUDED

#include "vertex_format.hpp"
#include "vertex.hpp"
#include "types.hpp"
#include "../shared_ptr.hpp"
#include "../algorithm.hpp"
#include "../export.hpp"
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <cstddef>

namespace sge
{

namespace vb_detail
{

template<typename Stored>
class iterator_impl : public boost::iterator_facade<iterator_impl<Stored>, Stored, std::random_access_iterator_tag, Stored, vertex_difference> {

	typedef boost::iterator_facade<iterator_impl<Stored>,Stored,std::random_access_iterator_tag,Stored, vertex_difference> base_type;
public:
	typedef typename base_type::difference_type   difference_type;
	typedef typename base_type::value_type        value_type;
	typedef typename base_type::reference         reference;
	typedef typename base_type::pointer           pointer;
	typedef typename base_type::iterator_category iterator_category;
	typedef vertex_size                           size_type;
private:
	friend class vertex_buffer;

	typename Stored::pointer data;
	size_type                stride;
	const offset_info*       oi;

	friend class boost::iterator_core_access;
	void advance(const difference_type d) { data += stride * d; }
	void increment() { data += stride; }
	void decrement() { data -= stride; }
	bool equal(const iterator_impl& r) const { return data == r.data; }
	difference_type distance_to(const iterator_impl& r) const { return (r.data - data) / difference_type(stride); }
	Stored dereference() const { return Stored(data,stride,*oi); }
	template<typename OtherStored> friend class iterator_impl;
public:
	template<typename OtherStored>
	iterator_impl(const iterator_impl<OtherStored>& r)
	 : data(r.data), stride(r.stride), oi(r.oi) {}

	iterator_impl(typename Stored::pointer data, const size_type stride, const offset_info& oi)
	 : data(data), stride(stride), oi(&oi)
	{}
};

typedef iterator_impl<vertex> iterator;
typedef iterator_impl<const_vertex> const_iterator;

}

class vertex_buffer {
public:
	typedef vertex::value_type      value_type;
	typedef vertex::size_type       size_type;
	typedef vertex::difference_type difference_type;
	typedef vertex                  reference;
	typedef const_vertex            const_reference;
	typedef vertex::pointer         pointer;
	typedef const_vertex::pointer   const_pointer;
	
	typedef vb_detail::iterator_impl<vertex>       iterator;
	typedef vb_detail::iterator_impl<const_vertex> const_iterator;

	typedef std::reverse_iterator<iterator>       reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	SGE_SYMBOL iterator end();
	SGE_SYMBOL const_iterator end() const;
	SGE_SYMBOL reverse_iterator rbegin();
	SGE_SYMBOL const_reverse_iterator rbegin() const;
	SGE_SYMBOL reverse_iterator rend();
	SGE_SYMBOL const_reverse_iterator rend() const;
	SGE_SYMBOL reference operator[](size_type);
	SGE_SYMBOL const_reference operator[](size_type) const;

	virtual void lock(lock_flag_t flags = lock_flags::default_) = 0;
	virtual void unlock() = 0;
	virtual void set_data(const_pointer data, size_type first, size_type count) = 0;

	virtual iterator begin() = 0;
	virtual const_iterator begin() const = 0;
	virtual size_type size() const = 0;
	virtual resource_flag_t flags() const = 0;

	virtual void resize(size_type newsize, const_pointer new_data = 0) = 0;
	virtual size_type stride() const = 0;
	virtual iterator create_iterator(pointer data) = 0;
	virtual const_iterator create_iterator(const_pointer data) const = 0;
	virtual pointer data() = 0;
	virtual const_pointer data() const = 0;

	virtual const vertex_format& get_vertex_format() const = 0;
	SGE_SYMBOL virtual ~vertex_buffer();
};

typedef shared_ptr<vertex_buffer> vertex_buffer_ptr;

}

#endif

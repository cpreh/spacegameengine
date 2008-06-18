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


#ifndef SGE_RENDERER_VERTEX_ITERATOR_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_ITERATOR_HPP_INCLUDED

#include "vertex.hpp"
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>

namespace sge
{
namespace renderer
{
namespace vb_detail
{

template<typename Stored>
class iterator_impl;

template<typename Stored>
struct typedef_helper {
	typedef boost::iterator_facade<
		iterator_impl<Stored>,
		Stored,
		std::random_access_iterator_tag,
		Stored,
		vertex_difference
	> type;
};

template<typename Stored>
class iterator_impl
: public typedef_helper<Stored>::type {
	typedef typename typedef_helper<Stored>::type base_type;
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
	
	void advance(const difference_type d)
	{
		data += stride * d;
	}
	
	void increment()
	{
		data += stride;
	}
	
	void decrement()
	{
		data -= stride;
	}
	
	bool equal(const iterator_impl& r) const
	{
		return data == r.data;
	}
	difference_type distance_to(const iterator_impl& r) const
	{
		return (r.data - data) / difference_type(stride);
	}
	
	Stored dereference() const
	{
		return Stored(data, stride, *oi);
	}
	template<typename OtherStored> friend class iterator_impl;
public:
	template<typename OtherStored>
	iterator_impl(
		iterator_impl<OtherStored> const &r)
	 : data(r.data),
	   stride(r.stride),
	   oi(r.oi)
	{}

	iterator_impl(
		typename Stored::pointer data,
		const size_type stride,
		const offset_info& oi)
	 : data(data),
	   stride(stride),
	   oi(&oi)
	{}
};

typedef iterator_impl<vertex> iterator;
typedef iterator_impl<const_vertex> const_iterator;

}
}
}

#endif


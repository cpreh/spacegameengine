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


#ifndef SGE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_VERTEX_FORMAT_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <tr1/type_traits>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include "../types.hpp"
#include "types.hpp"

namespace sge
{

enum vertex_usage {
	VU_Pos,
	VU_Normal,
	VU_Tex,
	VU_Diffuse,
	VU_num_elements
};

template<vertex_usage u> struct vertex_traits;
template<> struct vertex_traits<VU_Pos> {
	typedef space_unit                   element_type;
	typedef math::vector<element_type,3> packed_type;
};
template<> struct vertex_traits<VU_Normal> {
	typedef space_unit                   element_type;
	typedef math::vector<element_type,3> packed_type;
};
template<> struct vertex_traits<VU_Tex> {
	typedef space_unit                   element_type;
	typedef math::vector<element_type,2> packed_type;
};
template<> struct vertex_traits<VU_Diffuse> {
	typedef int          element_type;
	typedef element_type packed_type;
};

typedef std::size_t vertex_size;
typedef std::ptrdiff_t vertex_difference;

const vertex_size vertex_element_size[] = {
	3*sizeof(vertex_traits<VU_Pos>::element_type),
	3*sizeof(vertex_traits<VU_Normal>::element_type),
	2*sizeof(vertex_traits<VU_Tex>::element_type),
	1*sizeof(vertex_traits<VU_Diffuse>::element_type)
};

typedef vertex_size offset_info[VU_num_elements];

class vertex_element {
public:
	vertex_element(const vertex_usage _usage, const vertex_size _count)
	 : _usage(_usage), _count(_count), _size(vertex_element_size[_usage]) {}
	vertex_usage usage() const { return _usage; }
	vertex_size  size() const { return _size; }
	vertex_size  count() const { return _count; }
	vertex_size  stride() const { return size()*count(); }
private:
	vertex_usage  _usage;
	vertex_size   _count;
	vertex_size   _size;
};

class vertex_format {
public:
	typedef std::vector<vertex_element> usage_list;

	vertex_format() : _stride(0) {}

	const usage_list& elements() const { return ulist; }

	vertex_size stride() const { return _stride; }

	vertex_format& add(const vertex_usage u, const vertex_size count = 1)
	{
		oi[u] = _stride;
		ulist.push_back(vertex_element(u,count));
		_stride += vertex_element_size[u] * count;
		return *this;
	}

	const offset_info& offsets() const { return oi; }

	bool uses(const vertex_usage e) const
	{
		return std::find_if(ulist.begin(),ulist.end(),boost::lambda::bind(&vertex_element::usage,boost::lambda::_1) == e) != ulist.end();
	}
private:
	offset_info oi;
	usage_list  ulist;
	vertex_size _stride;
};

namespace detail
{

template<bool IsConst, typename T> struct return_type {
private:
	typedef typename boost::mpl::if_c<IsConst, typename boost::add_const<T>::type, T>::type cv_type;
public:
	typedef typename boost::add_reference<cv_type>::type type;
};

}

template<bool IsConst> class vertex_pointer_impl {
public:
	typedef char               value_type;
	typedef vertex_difference  difference_type;
	typedef vertex_size        size_type;
	typedef typename boost::mpl::if_c<IsConst, typename boost::add_const<value_type>::type, value_type>::type* pointer;

	template<vertex_usage U>
		typename detail::return_type<IsConst, typename vertex_traits<U>::packed_type>::type
	element(const vertex_size index = 0) const
	{
		typedef typename detail::return_type<IsConst, typename vertex_traits<U>::packed_type>::type type_to_cast;
		return reinterpret_cast<type_to_cast>(*(data + oi[U] + vertex_element_size[U] * index));
	}

	typename detail::return_type<IsConst, vertex_traits<VU_Pos    >::packed_type>::type pos() const { return element<VU_Pos>(); }
	typename detail::return_type<IsConst, vertex_traits<VU_Normal >::packed_type>::type normal() const { return element<VU_Normal>(); }
	typename detail::return_type<IsConst, vertex_traits<VU_Tex    >::packed_type>::type tex(const vertex_size index = 0) const { return element<VU_Tex>(index); }
	typename detail::return_type<IsConst, vertex_traits<VU_Diffuse>::packed_type>::type diffuse() const { return element<VU_Diffuse>(); }

	vertex_pointer_impl(const pointer data, const size_type stride, const offset_info& oi)
	 : data(data), stride(stride), oi(oi) {}

	template<bool OtherConst>
	vertex_pointer_impl(const vertex_pointer_impl<OtherConst>& o)
	 : data(o.data), stride(o.stride), oi(o.oi) {}
private:
	pointer data;
	size_type stride;
	const offset_info& oi;
};

typedef vertex_pointer_impl<true>  const_vertex_pointer;
typedef vertex_pointer_impl<false> vertex_pointer;

}

#endif

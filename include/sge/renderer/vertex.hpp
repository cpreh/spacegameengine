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


#ifndef SGE_RENDERER_VERTEX_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_HPP_INCLUDED

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/if.hpp>
#include "vertex_format.hpp"

namespace sge
{
namespace renderer
{

/*namespace vb_detail
{

template<bool IsConst, typename T>
struct return_type {
private:
	typedef typename boost::mpl::if_c<IsConst, typename boost::add_const<T>::type, T>::type cv_type;
public:
	typedef typename boost::add_reference<cv_type>::type type;
};

template<bool IsConst>
class vertex_impl {
public:
	typedef unsigned char      value_type;
	typedef vertex_difference  difference_type;
	typedef vertex_size        size_type;
	typedef typename boost::mpl::if_c<
		IsConst,
		typename boost::add_const<
			value_type>::type,
		value_type>::type *pointer;

	template<vertex_usage::type U>
		typename return_type<
			IsConst,
			typename vertex_traits<U>::packed_type>::type
	element(const vertex_size index = 0) const
	{
		typedef typename return_type<IsConst, typename vertex_traits<U>::packed_type>::type type_to_cast;
		return reinterpret_cast<type_to_cast>(*(data + oi[U] + vertex_element_size[U] * index));
	}

	typename return_type<IsConst, vertex_traits<vertex_usage::pos>::packed_type>::type pos() const
	{
		return element<vertex_usage::pos>();
	}

	typename return_type<IsConst, vertex_traits<vertex_usage::normal>::packed_type>::type normal() const
	{
		return element<vertex_usage::normal>();
	}

	typename return_type<IsConst, vertex_traits<vertex_usage::tex>::packed_type>::type tex(const vertex_size index = 0) const
	{
		return element<vertex_usage::tex>(index);
	}
	
	typename return_type<IsConst, vertex_traits<vertex_usage::diffuse>::packed_type>::type diffuse() const
	{
		return element<vertex_usage::diffuse>();
	}

	vertex_impl(
		const pointer data,
		const size_type stride,
		const offset_info& oi)
	 : data(data),
	   stride(stride),
	   oi(oi)
	{}

	template<bool OtherConst>
	explicit vertex_impl(vertex_impl<OtherConst> const& o)
	 : data(o.data), stride(o.stride), oi(o.oi) {}
private:
	pointer data;
	size_type stride;
	offset_info const &oi;
};

}

typedef vb_detail::vertex_impl<true>  const_vertex;
typedef vb_detail::vertex_impl<false> vertex;*/

}
}

#endif

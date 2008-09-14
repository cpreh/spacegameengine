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


#ifndef SGE_RENDERER_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_FORMAT_HPP_INCLUDED

#include "types.hpp"
#include <boost/array.hpp>
#include <vector>
#include <cstddef>

namespace sge
{
namespace renderer
{

/*namespace vertex_usage
{
	enum type {
		pos,
		normal,
		tex,
		diffuse,
		num_elements
	};
}

template<vertex_usage::type> struct vertex_traits;

template<> struct vertex_traits<vertex_usage::pos> {
	typedef space_unit                         element_type;
	typedef math::basic_vector<element_type,3> packed_type;
};

template<> struct vertex_traits<vertex_usage::normal> {
	typedef space_unit                         element_type;
	typedef math::basic_vector<element_type,3> packed_type;
};

template<> struct vertex_traits<vertex_usage::tex> {
	typedef space_unit                         element_type;
	typedef math::basic_vector<element_type,2> packed_type;
};

template<> struct vertex_traits<vertex_usage::diffuse> {
	typedef uint32       element_type; // FIXME
	typedef element_type packed_type;
};

typedef std::size_t vertex_size;
typedef std::ptrdiff_t vertex_difference;

const vertex_size vertex_element_size[] = {
	3*sizeof(vertex_traits<vertex_usage::pos>::element_type),
	3*sizeof(vertex_traits<vertex_usage::normal>::element_type),
	2*sizeof(vertex_traits<vertex_usage::tex>::element_type),
	1*sizeof(vertex_traits<vertex_usage::diffuse>::element_type)
};

typedef boost::array<vertex_size, vertex_usage::num_elements> offset_info;

class vertex_element {
public:
	SGE_SYMBOL vertex_element(vertex_usage::type usage, vertex_size count);
	SGE_SYMBOL vertex_usage::type usage() const;
	SGE_SYMBOL vertex_size size() const;
	SGE_SYMBOL vertex_size count() const;
	SGE_SYMBOL vertex_size stride() const;
private:
	vertex_usage::type usage_;
	vertex_size        count_;
	vertex_size        size_;
};

class vertex_format {
public:
	typedef std::vector<vertex_element> usage_list;

	SGE_SYMBOL vertex_format();
	SGE_SYMBOL const usage_list& elements() const;
	SGE_SYMBOL vertex_size stride() const;
	SGE_SYMBOL vertex_format& add(vertex_usage::type u, vertex_size count = 1);
	SGE_SYMBOL const offset_info& offsets() const;
	SGE_SYMBOL bool uses(vertex_usage::type e) const;
private:
	offset_info oi;
	usage_list  ulist;
	vertex_size stride_;
};*/

namespace vf
{

template<vertex_size NumElements>
struct element_base {
	static vertex_size const num_elements = NumElements;
};

template<vertex_size NumElements>
struct pos : element_base<NumElements> {
	typedef space_unit subelement_type;
	typedef math::vector3 packet_type;
	static vertex_size const num_subelements = 3;
};

template<typename Format, vertex_size NumElements>
struct color : element_base<NumElements> {
	typedef Format::channel_t subelement_type;
	typedef Format packet_type;
	static vertex_size const num_subelements = 4;
};

template<typename T>
struct element_stride
: boost::mpl::integral_c<
	vertex_size,
	sizeof(typename T::subelement_type)
	* T::num_subelements
>{};

template<typename T>
struct stride
: boost::mpl::integral_c<
	vertex_size,
	boost::mpl::multiply<
		element_size<T>,
		T::num_elements
	>
>{};

template<typename T>
struct packed_type {
	typedef typename T::packet_type packet_type;
};

}

template<typename Elements>
struct vertex_format {
	typedef Elements elements;

	typedef partial_sums<
		boost::mpl::transform<
			Elements,
			stride<
				boost::mpl::_1
			>
		>		
	>::type offsets;
};

template<typename VertexFormat>
class vertex {
public:
	typedef unsigned char internal_type;
	typedef internal_type *pointer;

	vertex(
		pointer const data)
	:
		data(data)
	{}

	template<typename T>
	void set(
		T const &t)
	{
		typedef typename boost::mpl::find_if<
			typename VertexFormat::elements,
			T,
			packed_type<
				boost::mpl::_1
			>
		>::type element;

		typedef typename boost::mpl::advance<
			boost::mpl::begin<
				typename VertexFormat::offsets
			>,
			boost::mpl::distance<
				typename VertexFormat::elements
				element
			>
		>::type offset;

		copy_n(
			reinterpret_cast<unsigned char const *>(
				t)
			+ offset::value,
			stride<element>::value,
			data);
	}
};

}
}

#endif

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
#include "color.hpp"
#include <boost/array.hpp>
#include <vector>
#include <cstddef>

namespace sge
{
namespace renderer
{

namespace vertex_usage
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
	typedef color        element_type;
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
};

}
}

#endif

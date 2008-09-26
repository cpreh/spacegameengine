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


#ifndef SGE_RENDERER_VF_VERTEX_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_HPP_INCLUDED

#include "../../algorithm/copy_n.hpp"
#include <boost/mpl/find.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/placeholders.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<typename VertexFormat>
class vertex {
public:
	typedef typename VertexFormat::pointer pointer;

	explicit vertex(
		pointer const data)
	:
		data(data)
	{}

	template<
		typename Field,
		typename T
	>
	void set(
		T const &t)
	{
		typedef typename boost::mpl::find<
			typename VertexFormat::elements,
			Field
		>::type element;
		
		typedef typename boost::mpl::advance<
			boost::mpl::begin<
				typename VertexFormat::offsets
			>,
			boost::mpl::distance<
				typename VertexFormat::elements,
				element
			>
		>::type offset;

		/*copy_n(
			reinterpret_cast<pointer>(
				t)
			+ offset::value,
			stride<element>::value,
			data);*/
	}

	/*
	template<
		typename Field
	>
	typename Field::packed_type const get() const
	{
		typedef typename boost::mpl::find<
			typename VertexFormat::elements,
			Field
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
	
		T ret;
		copy_n(
			data + offset::value,
			reinterpret_cast<pointer>(
				ret),
			stride<element>::value);
		return ret;
	}*/
private:
	pointer const data;	
};

}
}
}

#endif

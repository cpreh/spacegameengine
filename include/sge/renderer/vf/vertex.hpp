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
#include "../../mpl/find_nth.hpp"
#include "raw_data.hpp"
#include "element_stride.hpp"
#include "vertex_size.hpp"
#include <boost/mpl/find.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

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
	typedef typename VertexFormat::elements elements;
	typedef typename VertexFormat::offsets offsets;

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
			elements,
			Field
		>::type element;
	
		set_internal<element>(t);
	}

	template<
		typename Field,
		vertex_size Index,
		typename T
	>
	void set(
		T const &t)
	{
		typedef typename mpl::find_nth<
			elements,
			Field,
			boost::mpl::integral_c<
				vertex_size,
				Index
			>
		>::type element;

		set_internal<element>(t);
	}
private:
	template<
		typename Iter,
		typename T
	>
	void set_internal(
		T const &t)
	{
		BOOST_STATIC_ASSERT((
			!boost::is_same<
				typename boost::mpl::end<
					elements
				>::type,
				Iter
			>::value));

		typedef typename boost::mpl::advance<
			typename boost::mpl::begin<
				offsets
			>::type,
			boost::mpl::distance<
				typename boost::mpl::begin<
					elements
				>::type,
				Iter
			>
		>::type offset;

		copy_n(
			raw_data(t),
			element_stride<
				typename boost::mpl::deref<
					Iter
				>::type
			>::type::value,
			data + boost::mpl::deref<offset>::type::value);
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
	pointer const data;	
};

}
}
}

#endif

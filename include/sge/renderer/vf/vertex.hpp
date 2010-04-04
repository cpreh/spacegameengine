/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/vf/vertex_fwd.hpp>
#include <sge/renderer/vf/detail/raw_data.hpp>
#include <sge/renderer/vf/detail/calc_offset.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <fcppt/mpl/find_nth.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename VertexFormat
>
class vertex
{
public:
	typedef typename VertexFormat::pointer pointer;
	typedef typename VertexFormat::elements elements;
	typedef typename VertexFormat::offsets offsets;

	explicit vertex(
		pointer const data
	)
	:
		data(data)
	{}

	template<
		typename Field,
		typename T
	>
	void
	set(
		T const &t
	)
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
	void
	set(
		T const &t
	)
	{
		typedef typename fcppt::mpl::find_nth<
			elements,
			Field,
			boost::mpl::integral_c<
				vertex_size,
				Index
			>
		>::type element;

		set_internal<element>(t);
	}

	template<
		typename Field
	>
	typename Field::packed_type
	get() const
	{
		typedef typename boost::mpl::find<
			elements,
			Field
		>::type element;

		return get_internal<element>();
	}

	template<
		typename Field,
		vertex_size Index
	>
	typename Field::packed_type
	get() const
	{
		typedef typename fcppt::mpl::find_nth<
			elements,
			Field,
			boost::mpl::integral_c<
				vertex_size,
				Index
			>
		>::type element;

		return get_internal<element>();
	}
private:
	template<
		typename Iter,
		typename T
	>
	void
	set_internal(
		T const &t
	)
	{
		typedef typename detail::calc_offset<
			elements,
			offsets,
			Iter
		>::type offset;

		typedef typename boost::mpl::deref<
			Iter
		>::type element;

		BOOST_STATIC_ASSERT((
			boost::is_same<
				typename element::packed_type,
				T
			>::value)
		);

		fcppt::algorithm::copy_n(
			detail::raw_data(t),
			detail::element_stride<
				element
			>::type::value,
			data + boost::mpl::deref<offset>::type::value
		);
	}


	template<
		typename Iter
	>
	typename boost::mpl::deref<Iter>::type::packed_type const
	get_internal() const
	{
		typedef typename detail::calc_offset<
			elements,
			offsets,
			Iter
		>::type offset;

		typedef typename boost::mpl::deref<Iter>::type element;

		typedef typename element::packed_type packed_type;

		packed_type ret;

		fcppt::algorithm::copy_n(
			data + boost::mpl::deref<offset>::type::value,
			detail::element_stride<
				element
			>::type::value,
			const_cast<
				raw_pointer
			>(
				detail::raw_data(
					ret
				)
			)
		);

		return ret;
	}

	pointer const data;
};

}
}
}

#endif

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_VERTEX_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/vertex_decl.hpp>
#include <sge/renderer/vf/detail/calc_offset.hpp>
#include <sge/renderer/vf/detail/copy_n.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <sge/renderer/vf/detail/raw_data.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>

template<
	typename Part,
	typename Constness
>
sge::renderer::vf::vertex<Part, Constness>::vertex(
	pointer const _data
)
:
	data_(_data)
{
}

template<
	typename Part,
	typename Constness
>
template<
	typename Field
>
typename boost::enable_if<
	boost::mpl::contains<
		typename sge::renderer::vf::vertex<Part, Constness>::elements,
		Field
	>,
	void
>::type
sge::renderer::vf::vertex<Part, Constness>::set(
	typename Field::packed_type const &_value
)
{
	typedef typename boost::mpl::find<
		elements,
		Field
	>::type element_iterator;

	typedef typename detail::calc_offset<
		elements,
		offsets,
		element_iterator
	>::type offset;

	typedef typename boost::mpl::deref<
		element_iterator
	>::type element;

	detail::copy_n(
		detail::raw_data(
			_value
		),
		detail::element_stride<
			element
		>::type::value,
		data_ + boost::mpl::deref<offset>::type::value
	);
}

template<
	typename Part,
	typename Constness
>
template<
	typename Field
>
typename boost::enable_if<
	boost::mpl::contains<
		typename sge::renderer::vf::vertex<Part, Constness>::elements,
		Field
	>,
	typename Field::packed_type
>::type
sge::renderer::vf::vertex<Part, Constness>::get() const
{
	typedef typename boost::mpl::find<
		elements,
		Field
	>::type element_iterator;

	typedef typename detail::calc_offset<
		elements,
		offsets,
		element_iterator
	>::type offset;

	typedef typename boost::mpl::deref<element_iterator>::type element;

	typedef typename element::packed_type packed_type;

	packed_type ret;

	detail::copy_n(
		data_ + boost::mpl::deref<offset>::type::value,
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

#endif

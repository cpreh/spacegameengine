/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_FILL_GEOMETRY_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_GEOMETRY_HPP_INCLUDED

#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/detail/fill_indices.hpp>
#include <sge/sprite/detail/fill_vertices.hpp>
#include <sge/sprite/detail/optional_size.hpp>
#include <sge/sprite/detail/roles/index_buffer.hpp>
#include <sge/sprite/detail/roles/vertex_buffer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename It,
	typename Buffers
>
typename boost::enable_if<
	boost::mpl::contains<
		typename std::iterator_traits<
			It
		>::value_type::choices::elements,
		sprite::with_dim
	>,
	void
>::type
fill_geometry(
	It _begin,
	It const _end,
	Buffers const &_buffers,
	detail::optional_size const &_num_sprites
)
{
	detail::fill_indices<
		typename std::iterator_traits<
			It
		>::value_type::choices
	>(
		*_buffers.template get<
			detail::roles::index_buffer
		>(),
		detail::fill_vertices(
			_begin,
			_end,
			*_buffers.template get<
				detail::roles::vertex_buffer
			>(),
			_num_sprites
		)
	);
}

template<
	typename It,
	typename Buffers
>
typename boost::disable_if<
	boost::mpl::contains<
		typename std::iterator_traits<
			It
		>::value_type::choices::elements,
		sprite::with_dim
	>,
	void
>::type
fill_geometry(
	It _begin,
	It const _end,
	Buffers const &_buffers,
	detail::optional_size const &_num_sprites
)
{
	detail::fill_vertices(
		_begin,
		_end,
		*_buffers.template get<
			detail::roles::vertex_buffer
		>(),
		_num_sprites
	);
}

}
}
}

#endif

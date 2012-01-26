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


#ifndef SGE_SPRITE_RENDER_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/render/geometry.hpp>
#include <sge/sprite/detail/render/matrices.hpp>
#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/detail/render/scoped_states.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/render/is_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Options,
	typename Range,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::render::is_options<
		Options
	>,
	void
>::type
with_options(
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare
)
{
	if(
		_range.empty()
	)
		return;

	sge::sprite::detail::render::geometry<
		Options::geometry_options
	>(
		_range,
		_buffers,
		_compare
	);

	sge::sprite::detail::render::matrices<
		Options::matrix_options
	>(
		_buffers.renderer()
	);

	sge::sprite::detail::render::scoped_states<
		typename std::iterator_traits<
			typename Range::iterator
		>::value_type::choices,
		Options::state_options
	> const states(
		_buffers.renderer()
	);

	sge::sprite::detail::render::scoped_vertex<
		Options::vertex_options
	> const vertex(
		_buffers.renderer(),
		_buffers.vertex_declaration(),
		_buffers.vertex_buffer()
	);

	sge::sprite::detail::render::range(
		_range.begin(),
		_range.end(),
		_compare,
		_buffers
	);
}

}
}
}

#endif

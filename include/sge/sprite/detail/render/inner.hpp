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


#ifndef SGE_SPRITE_DETAIL_RENDER_INNER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_INNER_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices
>
typename boost::enable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	void
>::type
inner(
	sge::renderer::device &_renderer,
	sge::sprite::render::range<
		Choices
	> const &_range,
	sge::sprite::render::range_part<
		Choices
	> const &_range_part
)
{
	_renderer.render_indexed(
		_range.index_buffer(),
		_range_part.first_vertex(),
		_range_part.vertex_count(),
		sge::renderer::indexed_primitive_type::triangle,
		_range_part.primitive_count(),
		_range_part.first_index()
	);
}

template<
	typename Choices
>
typename boost::disable_if<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>,
	void
>::type
inner(
	sge::renderer::device &_renderer,
	sge::sprite::render::range<
		Choices
	> const &,
	sge::sprite::render::range_part<
		Choices
	> const &_range_part
)
{
	_renderer.render_nonindexed(
		_range_part.first_vertex(),
		_range_part.vertex_count(),
		sge::renderer::nonindexed_primitive_type::point
	);
}

}
}
}
}

#endif

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <fcppt/not.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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
inline
std::enable_if_t<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>::value,
	void
>
inner(
	sge::renderer::context::core &_render_context,
	sge::sprite::detail::render::range_object<
		Choices
	> const &_range,
	sge::sprite::render::range_part<
		Choices
	> const &_range_part
)
{
	_render_context.render_indexed(
		*fcppt::record::get<
			sge::sprite::buffers::roles::index_buffer
		>(
			_range
		),
		_range_part.first_vertex(),
		_range_part.vertex_count(),
		sge::renderer::primitive_type::triangle_list,
		_range_part.first_index(),
		_range_part.index_count()
	);
}

template<
	typename Choices
>
inline
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::needs_index_buffer<
			Choices
		>::value
	),
	void
>
inner(
	sge::renderer::context::core &_render_context,
	sge::sprite::detail::render::range_object<
		Choices
	> const &,
	sge::sprite::render::range_part<
		Choices
	> const &_range_part
)
{
	_render_context.render_nonindexed(
		_range_part.first_vertex(),
		_range_part.vertex_count(),
		sge::renderer::primitive_type::point_list
	);
}

}
}
}
}

#endif

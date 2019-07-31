//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

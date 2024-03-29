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

namespace sge::sprite::detail::render
{

template <typename Choices>
inline void inner(
    sge::renderer::context::core &_render_context, // NOLINT(google-runtime-references)
    sge::sprite::detail::render::range_object<Choices> const &_range,
    sge::sprite::render::range_part<Choices> const &_range_part)
  requires(sge::sprite::detail::config::needs_index_buffer<Choices>::value)
{
  _render_context.render_indexed(
      *fcppt::record::get<sge::sprite::buffers::roles::index_buffer>(_range),
      _range_part.first_vertex(),
      _range_part.vertex_count(),
      sge::renderer::primitive_type::triangle_list,
      _range_part.first_index(),
      _range_part.index_count());
}

template <typename Choices>
inline void inner(
    sge::renderer::context::core &_render_context, // NOLINT(google-runtime-references)
    sge::sprite::detail::render::range_object<Choices> const &,
    sge::sprite::render::range_part<Choices> const &_range_part)
  requires(fcppt::not_(sge::sprite::detail::config::needs_index_buffer<Choices>::value))
{
  _render_context.render_nonindexed(
      _range_part.first_vertex(),
      _range_part.vertex_count(),
      sge::renderer::primitive_type::point_list);
}
}

#endif

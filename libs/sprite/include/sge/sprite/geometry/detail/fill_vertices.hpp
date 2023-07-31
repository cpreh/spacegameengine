//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_VERTICES_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_VERTICES_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/detail/offset.hpp>
#include <sge/sprite/detail/vf/format_part_from_object.hpp>
#include <sge/sprite/geometry/detail/fill_color.hpp>
#include <sge/sprite/geometry/detail/fill_point_size.hpp>
#include <sge/sprite/geometry/detail/fill_position.hpp>
#include <sge/sprite/geometry/detail/fill_texture_levels.hpp>
#include <sge/sprite/geometry/detail/make_render_part.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Range, typename Compare, typename Choices>
sge::sprite::render::range<Choices> fill_vertices(
    Range const &_range,
    Compare const &_compare,
    sge::sprite::buffers::slice<Choices> const &_slice)
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  using result_type = sge::sprite::render::range<Choices>;

  using iterator = typename Range::iterator;

  iterator const begin(_range.begin());

  iterator const end(_range.end());

  using object_type = typename std::iterator_traits<iterator>::value_type;

  using choices = typename object_type::choices;

  sge::renderer::vertex::scoped_lock const vblock(
      fcppt::make_ref(_slice.vertex_buffer()),
      sge::renderer::lock_segment{
          sge::renderer::lock_segment::vector{_slice.first_vertex().get()},
          sge::renderer::lock_segment::dim{
              sge::sprite::buffers::vertex_count<Choices>(_range.size()).get()}},
      sge::renderer::lock_mode::writeonly);

  using vertex_view =
      sge::renderer::vf::view<sge::sprite::detail::vf::format_part_from_object<object_type>>;

  vertex_view const vertices(vblock.value());

  typename vertex_view::iterator vb_it(vertices.begin());

  using range_part_vector = typename result_type::range_part_vector;

  range_part_vector result;

  sge::sprite::detail::offset offset(0U);

  sge::sprite::count cur_count(0U);

  // TODO(philipp): Simplify this!
  for (iterator cur(begin); cur != end; ++cur)
  {
    iterator const next(std::next(cur));

    ++cur_count;

    object_type const &cur_sprite(*cur);

    if (next == end || _compare(cur_sprite, *next) || _compare(*next, cur_sprite))
    {
      result.push_back(
          sge::sprite::geometry::detail::make_render_part(_slice, offset, cur_count, cur_sprite));

      offset += sge::sprite::detail::offset{cur_count.get()};

      cur_count = sge::sprite::count(0U);
    }

    sge::sprite::geometry::detail::fill_position(vb_it, cur_sprite);

    sge::sprite::geometry::detail::fill_texture_levels(vb_it, cur_sprite);

    sge::sprite::geometry::detail::fill_color(vb_it, cur_sprite);

    sge::sprite::geometry::detail::fill_point_size(vb_it, cur_sprite);

    vb_it += sge::sprite::geometry::detail::vertices_per_sprite<choices>::value;
  }

  return result_type(_slice.buffer_object(), std::move(result));

FCPPT_PP_POP_WARNING
}

}

#endif

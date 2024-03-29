//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_HPP_INCLUDED

#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/geometry/detail/fill_indices.hpp>
#include <sge/sprite/geometry/detail/fill_vertices.hpp>
#include <sge/sprite/render/range.hpp>
#include <fcppt/not.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Range, typename Compare, typename Choices>
inline sge::sprite::render::range<Choices> fill(
    Range const &_range,
    Compare const &_compare,
    sge::sprite::buffers::slice<Choices> const &_slice)
  requires(sge::sprite::detail::config::needs_index_buffer<Choices>::value)
{
  sge::sprite::geometry::detail::fill_indices<Choices>(_range.size(), _slice);

  return sge::sprite::geometry::detail::fill_vertices(_range, _compare, _slice);
}

template <typename Range, typename Compare, typename Choices>
inline sge::sprite::render::range<Choices> fill(
    Range const &_range,
    Compare const &_compare,
    sge::sprite::buffers::slice<Choices> const &_slice)
  requires(fcppt::not_(sge::sprite::detail::config::needs_index_buffer<Choices>::value))
{
  return sge::sprite::geometry::detail::fill_vertices(_range, _compare, _slice);
}
}

#endif

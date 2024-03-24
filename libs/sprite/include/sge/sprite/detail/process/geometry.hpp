//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PROCESS_GEOMETRY_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PROCESS_GEOMETRY_HPP_INCLUDED

#include <sge/sprite/detail/process/is_same_geometry_options.hpp>
#include <sge/sprite/geometry/sort_and_update.hpp>
#include <sge/sprite/geometry/update.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/render/range_impl.hpp>

namespace sge::sprite::detail::process
{

template <
    sge::sprite::process::geometry_options Options,
    typename Choices,
    typename Range,
    typename Buffers,
    typename Compare>
inline sge::sprite::render::range<Choices>
geometry(Range const &_range, Buffers &_buffers, Compare const &_compare)
  requires(sge::sprite::detail::process::is_same_geometry_options<
           Options,
           sge::sprite::process::geometry_options::sort_and_update>::value)
{
  return sge::sprite::geometry::sort_and_update(_range, _compare, _buffers);
}

template <
    sge::sprite::process::geometry_options Options,
    typename Choices,
    typename Range,
    typename Buffers,
    typename Compare>
inline sge::sprite::render::range<Choices>
geometry(Range const &_range, Buffers &_buffers, Compare const &_compare)
  requires(sge::sprite::detail::process::is_same_geometry_options<
           Options,
           sge::sprite::process::geometry_options::update>::value)
{
  return sge::sprite::geometry::update(_range, _compare, _buffers);
}
}

#endif

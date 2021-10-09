//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_INDEX_COUNT_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_INDEX_COUNT_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/geometry/detail/indices_per_sprite.hpp>

namespace sge::sprite::buffers
{

template <typename Choices>
inline sge::renderer::index::count index_count(sge::sprite::count const _sprites)
{
  return sge::renderer::index::count(
      _sprites.get() * sge::sprite::geometry::detail::indices_per_sprite<Choices>::value);
}

}

#endif

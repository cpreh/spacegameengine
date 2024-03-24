//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_BUFFERS_ZERO_OFFSET_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ZERO_OFFSET_HPP_INCLUDED

#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/offset_object.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/not.hpp>

namespace sge::sprite::detail::buffers
{

template <typename Choices>
inline sge::sprite::buffers::offset_object<Choices> zero_offset()
  requires(sge::sprite::detail::config::needs_index_buffer<Choices>::value)
{
  return sge::sprite::buffers::offset_object<Choices>(
      sge::sprite::buffers::roles::first_vertex{} = sge::renderer::vertex::first{0U},
      sge::sprite::buffers::roles::first_index{} = sge::renderer::index::first{0U});
}

template <typename Choices>
inline sge::sprite::buffers::offset_object<Choices> zero_offset()
  requires(fcppt::not_(sge::sprite::detail::config::needs_index_buffer<Choices>::value))
{
  return sge::sprite::buffers::offset_object<Choices>(
      sge::sprite::buffers::roles::first_vertex{} = sge::renderer::vertex::first{0U});
}
}

#endif

//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/buffers/allocate_indices.hpp>
#include <sge/sprite/detail/buffers/allocate_vertices.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/not.hpp>

namespace sge::sprite::detail::buffers
{

template <typename Choices>
inline sge::sprite::buffers::object<Choices> allocate(
    sge::renderer::device::core_ref const _renderer,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::sprite::count const _num_sprites,
    sge::renderer::resource_flags_field const &_resource_flags)
  requires(sge::sprite::detail::config::needs_index_buffer<Choices>::value)
{
  return sge::sprite::buffers::object<Choices>{
      sge::sprite::buffers::roles::vertex_buffer{} =
          sge::sprite::detail::buffers::allocate_vertices<Choices>(
              _renderer, _vertex_declaration, _num_sprites, _resource_flags),
      sge::sprite::buffers::roles::index_buffer{} =
          sge::sprite::detail::buffers::allocate_indices<Choices>(
              _renderer, _num_sprites, _resource_flags)};
}

template <typename Choices>
inline sge::sprite::buffers::object<Choices> allocate(
    sge::renderer::device::core_ref const _renderer,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::sprite::count const _num_sprites,
    sge::renderer::resource_flags_field const &_resource_flags)
  requires(fcppt::not_(sge::sprite::detail::config::needs_index_buffer<Choices>::value))
{
  return sge::sprite::buffers::object<Choices>(
      sge::sprite::buffers::roles::vertex_buffer{} =
          sge::sprite::detail::buffers::allocate_vertices<Choices>(
              _renderer, _vertex_declaration, _num_sprites, _resource_flags));
}
}

#endif

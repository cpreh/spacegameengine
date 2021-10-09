//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_WITH_DECLARATION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_WITH_DECLARATION_IMPL_HPP_INCLUDED

#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/make_vertex_format.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <fcppt/make_cref.hpp>

template <typename Buffers>
sge::sprite::buffers::with_declaration<Buffers>::with_declaration(
    sge::renderer::device::core_ref const _device,
    sge::sprite::buffers::option const _buffers_option)
    : vertex_declaration_(
          _device.get().create_vertex_declaration(sge::renderer::vertex::declaration_parameters(
              sge::sprite::make_vertex_format<typename Buffers::choices>()))),
      buffers_(_device, fcppt::make_cref(*vertex_declaration_), _buffers_option)
{
}

namespace sge::sprite::buffers
{
template <typename Buffers>
with_declaration<Buffers>::~with_declaration() = default;
}

template <typename Buffers>
typename sge::sprite::buffers::with_declaration<Buffers>::slice_type
sge::sprite::buffers::with_declaration<Buffers>::allocate(sge::sprite::count const _count)
{
  return buffers_.allocate(_count);
}

template <typename Buffers>
typename sge::sprite::buffers::with_declaration<Buffers>::buffers_type &
sge::sprite::buffers::with_declaration<Buffers>::impl()
{
  return buffers_;
}

template <typename Buffers>
typename sge::sprite::buffers::with_declaration<Buffers>::buffers_type const &
sge::sprite::buffers::with_declaration<Buffers>::impl() const
{
  return buffers_;
}

template <typename Buffers>
sge::renderer::vertex::declaration const &
sge::sprite::buffers::with_declaration<Buffers>::vertex_declaration() const
{
  return *vertex_declaration_;
}

#endif

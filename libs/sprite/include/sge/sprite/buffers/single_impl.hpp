//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_SINGLE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SINGLE_IMPL_HPP_INCLUDED

#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer.hpp> // IWYU pragma: keep
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/allocate.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <sge/sprite/buffers/single_decl.hpp> // IWYU pragma: export
#include <sge/sprite/buffers/slice_impl.hpp> // IWYU pragma: keep
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/buffers/zero_offset.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp> // IWYU pragma: keep
#include <fcppt/record/get.hpp>

template <typename Choices>
sge::sprite::buffers::single<Choices>::single(
    sge::renderer::device::core_ref const _renderer,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::sprite::buffers::option const _buffers_option)
    : renderer_{_renderer},
      vertex_declaration_{_vertex_declaration},
      buffers_option_(_buffers_option),
      buffers_object_{}
{
}

namespace sge::sprite::buffers
{
template <typename Choices>
single<Choices>::~single() = default;
}

template <typename Choices>
typename sge::sprite::buffers::single<Choices>::slice_type
sge::sprite::buffers::single<Choices>::allocate(sge::sprite::count const _num_sprites)
{
  return slice_type(
      fcppt::optional::maybe(
          buffers_object_,
          [this, _num_sprites]()
          {
            return fcppt::make_cref(fcppt::optional::assign(
                buffers_object_,
                sge::sprite::buffers::allocate<Choices>(
                    renderer_,
                    vertex_declaration_,
                    _num_sprites,
                    sge::sprite::buffers::option_to_resource_flags(buffers_option_))));
          },
          [this, _num_sprites](buffers_object &_buffers)
          {
            if (fcppt::record::get<sge::sprite::buffers::roles::vertex_buffer>(_buffers)
                    ->linear_size() <
                sge::sprite::buffers::vertex_count<Choices>(_num_sprites).get())
            {
              _buffers = sge::sprite::buffers::allocate<Choices>(
                  renderer_,
                  vertex_declaration_,
                  _num_sprites,
                  sge::sprite::buffers::option_to_resource_flags(buffers_option_));
            }

            return fcppt::make_cref(_buffers);
          }),
      sge::sprite::buffers::zero_offset<Choices>());
}

template <typename Choices>
sge::renderer::vertex::declaration const &
sge::sprite::buffers::single<Choices>::vertex_declaration() const
{
  return vertex_declaration_.get();
}

#endif

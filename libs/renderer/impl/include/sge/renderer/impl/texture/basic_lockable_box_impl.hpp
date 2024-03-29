//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_TEXTURE_BASIC_LOCKABLE_BOX_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_TEXTURE_BASIC_LOCKABLE_BOX_IMPL_HPP_INCLUDED

#include <sge/renderer/basic_dim.hpp> // IWYU pragma: keep
#include <sge/renderer/buffer/readable.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/basic_lockable_box.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>

template <typename Tag>
sge::renderer::texture::basic_lockable_box<Tag>::basic_lockable_box()
    : sge::renderer::texture::base()
{
}

namespace sge::renderer::texture
{
template <typename Tag>
basic_lockable_box<Tag>::~basic_lockable_box() = default;
}

template <typename Tag>
typename sge::renderer::texture::basic_lockable_box<Tag>::dim
sge::renderer::texture::basic_lockable_box<Tag>::size() const
{
  return this->level(sge::renderer::texture::mipmap::level(0U)).size();
}

#endif

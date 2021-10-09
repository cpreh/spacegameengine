//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_TEXTURE_CONST_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_TEXTURE_CONST_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/image/view/const_object.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/texture/const_basic_scoped_lock.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_cref.hpp>

template <typename Tag>
sge::renderer::texture::const_basic_scoped_lock<Tag>::const_basic_scoped_lock(
    texture_ref const _texture)
    : lock_(fcppt::make_cref(_texture.get().level(sge::renderer::texture::mipmap::level(0U))))
{
}

template <typename Tag>
sge::renderer::texture::const_basic_scoped_lock<Tag>::const_basic_scoped_lock(
    texture_ref const _texture, lock_area const &_area)
    : lock_(
          fcppt::make_cref(_texture.get().level(sge::renderer::texture::mipmap::level(0U))), _area)
{
}

template <typename Tag>
typename sge::renderer::texture::const_basic_scoped_lock<Tag>::const_view
sge::renderer::texture::const_basic_scoped_lock<Tag>::value() const
{
  return lock_.value();
}

namespace sge::renderer::texture
{
template <typename Tag>
const_basic_scoped_lock<Tag>::~const_basic_scoped_lock() = default;
}

#endif

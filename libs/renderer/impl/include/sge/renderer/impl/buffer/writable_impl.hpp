//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_BUFFER_WRITABLE_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_BUFFER_WRITABLE_IMPL_HPP_INCLUDED

#include <sge/image/view/object.hpp> // IWYU pragma: keep
#include <sge/renderer/basic_dim.hpp> // IWYU pragma: keep
#include <sge/renderer/basic_lock_box.hpp> // IWYU pragma: keep
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/buffer/writable.hpp>
#include <fcppt/math/vector/null.hpp>

template <typename Tag>
sge::renderer::buffer::writable<Tag>::writable() : base()
{
}

namespace sge::renderer::buffer
{
template <typename Tag>
writable<Tag>::~writable() = default;
}

template <typename Tag>
typename sge::renderer::buffer::writable<Tag>::view
sge::renderer::buffer::writable<Tag>::lock(sge::renderer::lock_mode const _mode)
{
  return this->lock(
      lock_area{fcppt::math::vector::null<typename lock_area::vector>(), this->size()}, _mode);
}

#endif

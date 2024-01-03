//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_BUFFER_READABLE_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_BUFFER_READABLE_IMPL_HPP_INCLUDED

#include <sge/image/view/const_object.hpp> // IWYU pragma: keep
#include <sge/renderer/basic_dim.hpp> // IWYU pragma: keep
#include <sge/renderer/basic_lock_box.hpp> // IWYU pragma: keep
#include <sge/renderer/buffer/readable.hpp>
#include <fcppt/math/vector/null.hpp>

template <typename Tag>
sge::renderer::buffer::readable<Tag>::readable() : base_type()
{
}

namespace sge::renderer::buffer
{
template <typename Tag>
readable<Tag>::~readable() = default;
}

template <typename Tag>
typename sge::renderer::buffer::readable<Tag>::const_view
sge::renderer::buffer::readable<Tag>::lock_c() const
{
  return this->lock_c(
      lock_area{fcppt::math::vector::null<typename lock_area::vector>(), this->size()});
}

#endif

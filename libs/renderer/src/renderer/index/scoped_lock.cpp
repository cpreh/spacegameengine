//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/impl/buffer/instantiate_scoped_lock.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_ref.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/tag.hpp>
#include <fcppt/reference_to_base.hpp>

sge::renderer::index::scoped_lock::scoped_lock(
    sge::renderer::index::buffer_ref const _buffer, sge::renderer::lock_mode const _mode)
    : impl_{fcppt::reference_to_base<impl::buffer_type>(_buffer), _mode}
{
}

sge::renderer::index::scoped_lock::scoped_lock(
    sge::renderer::index::buffer_ref const _buffer,
    lock_area const &_area,
    sge::renderer::lock_mode const _mode)
    : impl_{fcppt::reference_to_base<impl::buffer_type>(_buffer), _area, _mode}
{
}

sge::renderer::index::scoped_lock::view sge::renderer::index::scoped_lock::value() const
{
  return this->impl_.value();
}

sge::renderer::index::scoped_lock::~scoped_lock() = default;

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_SCOPED_LOCK(sge::renderer::index::tag);

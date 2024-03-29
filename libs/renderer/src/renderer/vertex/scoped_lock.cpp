//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/impl/buffer/instantiate_scoped_lock.hpp>
#include <sge/renderer/vertex/buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vertex/buffer_ref.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <fcppt/reference_to_base.hpp>

sge::renderer::vertex::scoped_lock::scoped_lock(
    sge::renderer::vertex::buffer_ref const _buffer, sge::renderer::lock_mode const _mode)
    : impl_{fcppt::reference_to_base<impl::buffer_type>(_buffer), _mode}
{
}

sge::renderer::vertex::scoped_lock::scoped_lock(
    sge::renderer::vertex::buffer_ref const _buffer,
    lock_area const &_area,
    sge::renderer::lock_mode const _mode)
    : impl_{fcppt::reference_to_base<impl::buffer_type>(_buffer), _area, _mode}
{
}

sge::renderer::vertex::scoped_lock::view sge::renderer::vertex::scoped_lock::value() const
{
  return impl_.value();
}

sge::renderer::vertex::scoped_lock::~scoped_lock() = default;

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_SCOPED_LOCK(sge::renderer::vertex::tag);

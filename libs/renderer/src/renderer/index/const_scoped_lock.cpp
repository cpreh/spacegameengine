//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/impl/buffer/instantiate_const_scoped_lock.hpp>
#include <sge/renderer/index/buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/index/const_buffer_ref.hpp>
#include <sge/renderer/index/const_scoped_lock.hpp>
#include <sge/renderer/index/tag.hpp>
#include <fcppt/reference_to_base.hpp>

sge::renderer::index::const_scoped_lock::const_scoped_lock(
    sge::renderer::index::const_buffer_ref const _buffer)
    : impl_{fcppt::reference_to_base<impl::buffer_type const>(_buffer)}
{
}

sge::renderer::index::const_scoped_lock::const_scoped_lock(
    sge::renderer::index::const_buffer_ref const _buffer, lock_area const &_area)
    : impl_{fcppt::reference_to_base<impl::buffer_type const>(_buffer), _area}
{
}

sge::renderer::index::const_scoped_lock::view sge::renderer::index::const_scoped_lock::value() const
{
  return this->impl_.value();
}

sge::renderer::index::const_scoped_lock::~const_scoped_lock() = default;

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_CONST_SCOPED_LOCK(sge::renderer::index::tag);

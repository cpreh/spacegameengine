//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/debug_drawer.hpp>
#include <sge/projectile/world_ref.hpp>
#include <sge/projectile/impl/detail/debug_drawer_impl.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_reference.hpp>

sge::projectile::debug_drawer::debug_drawer(
    fcppt::log::context_reference const _log,
    sge::projectile::world_ref const _world,
    sge::renderer::device::core_ref const _renderer)
    : impl_(fcppt::make_unique_ptr<sge::projectile::detail::debug_drawer_impl>(
          _log, _world, _renderer))
{
}

void sge::projectile::debug_drawer::update() { impl_->update(); }

void sge::projectile::debug_drawer::render(sge::renderer::context::core &_render_context)
{
  impl_->render(_render_context);
}

void sge::projectile::debug_drawer::active(bool const _active) { impl_->active(_active); }

bool sge::projectile::debug_drawer::active() const { return impl_->active(); }

sge::projectile::debug_drawer::~debug_drawer() = default;

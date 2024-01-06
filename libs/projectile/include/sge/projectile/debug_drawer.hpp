//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED
#define SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED

#include <sge/projectile/debug_drawer_fwd.hpp> // IWYU pragma: keep
#include <sge/projectile/world_ref.hpp>
#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>

namespace sge::projectile
{
/// bullet offers registering a debug drawer to draw contact points or
/// just shapes. This class implements this interface, caching all the
/// lines and drawing them at once (if you don't do that, it'll be
/// super-slow).
class debug_drawer
{
  FCPPT_NONMOVABLE(debug_drawer);

public:
  SGE_PROJECTILE_DETAIL_SYMBOL
  debug_drawer(
      fcppt::log::context_reference, sge::projectile::world_ref, sge::renderer::device::core_ref);

  // Updates the line cache
  SGE_PROJECTILE_DETAIL_SYMBOL
  void update();

  // Renders the lines
  SGE_PROJECTILE_DETAIL_SYMBOL
  void render(sge::renderer::context::core & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  SGE_PROJECTILE_DETAIL_SYMBOL
  void active(bool);

  [[nodiscard]] SGE_PROJECTILE_DETAIL_SYMBOL bool active() const;

  SGE_PROJECTILE_DETAIL_SYMBOL
  ~debug_drawer();

private:
  fcppt::unique_ptr<sge::projectile::detail::debug_drawer_impl> const impl_;
};
}

#endif

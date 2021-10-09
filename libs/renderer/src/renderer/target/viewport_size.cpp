//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sge::renderer::screen_size
sge::renderer::target::viewport_size(sge::renderer::target::base const &_target)
{
  return fcppt::math::dim::structure_cast<sge::renderer::screen_size, fcppt::cast::to_unsigned_fun>(
      _target.viewport().get().size());
}

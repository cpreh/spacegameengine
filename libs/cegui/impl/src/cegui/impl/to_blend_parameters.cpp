//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/impl/to_blend_parameters.hpp>
#include <sge/renderer/state/core/blend/alpha_dest.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/alpha_source.hpp>
#include <sge/renderer/state/core/blend/color_dest.hpp>
#include <sge/renderer/state/core/blend/color_source.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Renderer.h>
#include <fcppt/config/external_end.hpp>

sge::renderer::state::core::blend::alpha_enabled
sge::cegui::impl::to_blend_parameters(CEGUI::BlendMode const _mode)
{
  switch (_mode)
  {
  case CEGUI::BM_RTT_PREMULTIPLIED:
    return sge::renderer::state::core::blend::alpha_enabled(
        sge::renderer::state::core::blend::combined(
            sge::renderer::state::core::blend::source::one,
            sge::renderer::state::core::blend::dest::inv_src_alpha));
  case CEGUI::BM_NORMAL:
    return
        // TODO(philipp): Check if this is supported!
        sge::renderer::state::core::blend::alpha_enabled(
            sge::renderer::state::core::blend::separate(
                sge::renderer::state::core::blend::color_source(
                    sge::renderer::state::core::blend::source::src_alpha),
                sge::renderer::state::core::blend::color_dest(
                    sge::renderer::state::core::blend::dest::inv_src_alpha),
                sge::renderer::state::core::blend::alpha_source(
                    sge::renderer::state::core::blend::source::inv_dest_alpha),
                sge::renderer::state::core::blend::alpha_dest(
                    sge::renderer::state::core::blend::dest::one)));
  case CEGUI::BM_INVALID:
    break;
  }

  FCPPT_ASSERT_UNREACHABLE;
}

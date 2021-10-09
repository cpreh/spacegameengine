//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_TO_BLEND_PARAMETERS_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TO_BLEND_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/state/core/blend/alpha_enabled_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Renderer.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cegui::impl
{

sge::renderer::state::core::blend::alpha_enabled to_blend_parameters(CEGUI::BlendMode);

}

#endif

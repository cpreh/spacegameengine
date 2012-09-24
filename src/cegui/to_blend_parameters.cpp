/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/renderer/state/core/blend/alpha_dest.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/alpha_source.hpp>
#include <sge/renderer/state/core/blend/color_dest.hpp>
#include <sge/renderer/state/core/blend/color_source.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <sge/src/cegui/to_blend_parameters.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Renderer.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::core::blend::alpha_enabled const
sge::cegui::to_blend_parameters(
	CEGUI::BlendMode const _mode
)
{
	switch(
		_mode
	)
	{
	case CEGUI::BM_RTT_PREMULTIPLIED:
		return
			sge::renderer::state::core::blend::alpha_enabled(
				sge::renderer::state::core::blend::combined(
					sge::renderer::state::core::blend::source::one,
					sge::renderer::state::core::blend::dest::inv_src_alpha
				)
			);
	case CEGUI::BM_NORMAL:
		return
			// TODO: Check if this is supported!
			sge::renderer::state::core::blend::alpha_enabled(
				sge::renderer::state::core::blend::separate(
					sge::renderer::state::core::blend::color_source(
						sge::renderer::state::core::blend::source::src_alpha
					),
					sge::renderer::state::core::blend::color_dest(
						sge::renderer::state::core::blend::dest::inv_src_alpha
					),
					sge::renderer::state::core::blend::alpha_source(
						sge::renderer::state::core::blend::source::inv_dest_alpha
					),
					sge::renderer::state::core::blend::alpha_dest(
						sge::renderer::state::core::blend::dest::one
					)
				)
			);
	case CEGUI::BM_INVALID:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

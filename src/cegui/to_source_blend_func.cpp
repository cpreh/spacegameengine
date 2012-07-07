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


#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/src/cegui/to_source_blend_func.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Renderer.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::source_blend_func::type
sge::cegui::to_source_blend_func(
	CEGUI::BlendMode const _mode
)
{
	switch(
		_mode
	)
	{
	case CEGUI::BM_RTT_PREMULTIPLIED:
		return
			sge::renderer::state::source_blend_func::one;
	case CEGUI::BM_NORMAL:
		return
			sge::renderer::state::source_blend_func::src_alpha;
	case CEGUI::BM_INVALID:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

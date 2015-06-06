/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::source_blend_func(
	sge::renderer::state::core::blend::source const _func
)
{
	switch(
		_func
	)
	{
	case sge::renderer::state::core::blend::source::zero:
		return
			GL_ZERO;
	case sge::renderer::state::core::blend::source::one:
		return
			GL_ONE;
	case sge::renderer::state::core::blend::source::dest_color:
		return
			GL_DST_COLOR;
	case sge::renderer::state::core::blend::source::inv_dest_color:
		return
			GL_ONE_MINUS_DST_COLOR;
	case sge::renderer::state::core::blend::source::src_alpha:
		return
			GL_SRC_ALPHA;
	case sge::renderer::state::core::blend::source::inv_src_alpha:
		return
			GL_ONE_MINUS_SRC_ALPHA;
	case sge::renderer::state::core::blend::source::dest_alpha:
		return
			GL_DST_ALPHA;
	case sge::renderer::state::core::blend::source::inv_dest_alpha:
		return
			GL_ONE_MINUS_DST_ALPHA;
	case sge::renderer::state::core::blend::source::src_alpha_sat:
		return
			GL_SRC_ALPHA_SATURATE;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

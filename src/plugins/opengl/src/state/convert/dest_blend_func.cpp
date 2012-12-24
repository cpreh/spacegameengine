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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::dest_blend_func(
	sge::renderer::state::core::blend::dest const _func
)
{
	switch(
		_func
	)
	{
	case sge::renderer::state::core::blend::dest::zero:
		return GL_ZERO;
	case sge::renderer::state::core::blend::dest::one:
		return GL_ONE;
	case sge::renderer::state::core::blend::dest::src_color:
		return GL_SRC_COLOR;
	case sge::renderer::state::core::blend::dest::inv_src_color:
		return GL_ONE_MINUS_SRC_COLOR;
	case sge::renderer::state::core::blend::dest::src_alpha:
		return GL_SRC_ALPHA;
	case sge::renderer::state::core::blend::dest::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case sge::renderer::state::core::blend::dest::dest_alpha:
		return GL_DST_ALPHA;
	case sge::renderer::state::core::blend::dest::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

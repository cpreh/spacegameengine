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
#include <sge/opengl/state/convert/bool.hpp>
#include <sge/renderer/state/bool/available_states.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::bool_(
	renderer::state::bool_::available_states::type const _state
)
{
	namespace rs = renderer::state::bool_::available_states;

	switch(
		_state
	)
	{
	case rs::enable_alpha_blending:
		return GL_BLEND;
	case rs::enable_lighting:
		return GL_LIGHTING;
	case rs::enable_scissor_test:
		return GL_SCISSOR_TEST;
	case rs::clear_back_buffer:
	case rs::clear_depth_buffer:
	case rs::clear_stencil_buffer:
	case rs::enable_point_sprites:
	case rs::write_to_depth_buffer:
	case rs::write_alpha:
	case rs::write_blue:
	case rs::write_green:
	case rs::write_red:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

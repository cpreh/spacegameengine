/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../clear_bit.hpp"
#include <sge/renderer/state/trampoline.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::clear_bit(
	renderer::state::bool_::trampoline_type const &_state
)
{
	namespace rs = sge::renderer::state::bool_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::clear_backbuffer:
		return GL_COLOR_BUFFER_BIT;
	case rs::clear_zbuffer:
		return GL_DEPTH_BUFFER_BIT;
	case rs::clear_stencil:
		return GL_STENCIL_BUFFER_BIT;
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
	case rs::enable_multi_sampling:
	case rs::enable_point_sprites:
	case rs::enable_scissor_test:
	case rs::write_to_zbuffer:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid bool_state in convert_clear_bit()!")
	);
}

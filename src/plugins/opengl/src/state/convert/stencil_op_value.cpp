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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/stencil_op_value.hpp>
#include <sge/renderer/state/stencil_op_value.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::stencil_op_value(
	sge::renderer::state::stencil_op_value::type const _value
)
{
	switch(
		_value
	)
	{
	case sge::renderer::state::stencil_op_value::keep:
		return GL_KEEP;
	case sge::renderer::state::stencil_op_value::zero:
		return GL_ZERO;
	case sge::renderer::state::stencil_op_value::replace:
		return GL_REPLACE;
	case sge::renderer::state::stencil_op_value::inc_sat:
		return GL_INCR;
	case sge::renderer::state::stencil_op_value::inc_wrap:
		return GL_INCR_WRAP;
	case sge::renderer::state::stencil_op_value::dec_sat:
		return GL_DECR;
	case sge::renderer::state::stencil_op_value::dec_wrap:
		return GL_DECR_WRAP;
	case sge::renderer::state::stencil_op_value::invert:
		return GL_INVERT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

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


#include "../source_blend_func.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::source_blend_func(
	renderer::state::source_blend_func::type const f
)
{
	switch(f) {
	case renderer::state::source_blend_func::zero:
		return GL_ZERO;
	case renderer::state::source_blend_func::one:
		return GL_ONE;
	case renderer::state::source_blend_func::dest_color:
		return GL_DST_COLOR;
	case renderer::state::source_blend_func::inv_dest_color:
		return GL_ONE_MINUS_DST_COLOR;
	case renderer::state::source_blend_func::src_alpha:
		return GL_SRC_ALPHA;
	case renderer::state::source_blend_func::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case renderer::state::source_blend_func::dest_alpha:
		return GL_DST_ALPHA;
	case renderer::state::source_blend_func::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case renderer::state::source_blend_func::src_alpha_sat:
		return GL_SRC_ALPHA_SATURATE;
	}

	throw exception(
		FCPPT_TEXT("Invalid source_blend_func!")
	);
}

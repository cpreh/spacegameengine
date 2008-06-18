/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../error.hpp"
#include "../texture_stage.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

namespace
{

GLenum stage_value_scale(
	const sge::renderer::texture_stage_op_value::type value)
{
	switch(value) {
	case sge::renderer::texture_stage_op_value::arg0:
	case sge::renderer::texture_stage_op_value::modulate:
	case sge::renderer::texture_stage_op_value::add:
	case sge::renderer::texture_stage_op_value::substract:
	case sge::renderer::texture_stage_op_value::add_signed:
	case sge::renderer::texture_stage_op_value::interpolate:
		return 1;
	case sge::renderer::texture_stage_op_value::modulate2x:
	case sge::renderer::texture_stage_op_value::add2x:
	case sge::renderer::texture_stage_op_value::add_signed2x:
		return 2;
	case sge::renderer::texture_stage_op_value::modulate4x:
	case sge::renderer::texture_stage_op_value::add4x:
		return 4;
	default:
		throw sge::exception(SGE_TEXT("Invalid texture_stage_op_value!"));
	}
}

}

void sge::ogl::tex_envf_ext(const GLenum arg, const GLenum value)
{
	SGE_OPENGL_SENTRY
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, arg, value); // FIXME
}

void sge::ogl::set_texture_stage_scale(const renderer::texture_stage_op_value::type value)
{
	const GLenum scale = stage_value_scale(value);
	tex_envf_ext(GL_RGB_SCALE, scale);
	tex_envf_ext(GL_ALPHA_SCALE, scale);
}

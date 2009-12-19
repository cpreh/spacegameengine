/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../texture_stage.hpp"
#include "../check_state.hpp"
#include "../convert/texture_stage_op.hpp"
#include "../convert/texture_stage_op_value.hpp"
#include "../convert/texture_stage_arg.hpp"
#include "../convert/texture_stage_arg_value.hpp"
#include "../multi_texture.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

namespace
{

GLenum
stage_value_scale(
	sge::renderer::texture_stage_op_value::type const value
)
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
		throw sge::exception(
			FCPPT_TEXT("Invalid texture_stage_op_value!")
		);
	}
}

void tex_env_f(
	GLenum const type,
	GLenum const arg,
	GLfloat const value)
{
	glTexEnvf(
		type,
		arg,
		value
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexEnvf failed"),
		sge::renderer::exception
	)
}

}

void sge::opengl::tex_envf_ext(
	GLenum const arg,
	GLenum const value)
{
	tex_env_f(
		GL_TEXTURE_ENV,
		GL_TEXTURE_ENV_MODE,
		GL_COMBINE
	);

	tex_env_f(
		GL_TEXTURE_ENV,
		arg,
		static_cast<GLfloat>(value)
	);
}

void sge::opengl::set_texture_stage_scale(
	renderer::texture_stage_op_value::type const value)
{
	GLenum const scale = stage_value_scale(value);

	tex_envf_ext(
		GL_RGB_SCALE,
		scale
	);
	tex_envf_ext(
		GL_ALPHA_SCALE,
		scale
	);
}

template<
	typename Arg,
	typename Value
>
void
sge::opengl::set_texture_stage(
	renderer::stage_type const stage,
	Arg const arg,
	Value const value
)
{
	set_texture_level(
		stage
	);

	tex_envf_ext(
		convert::texture_stage(
			arg
		),
		convert::texture_stage_value(
			value
		)
	);
}

#define SGE_OPENGL_INSTANTIATE_SET_TEXTURE_STAGE(arg, value)\
template void sge::opengl::set_texture_stage(\
	sge::renderer::stage_type,\
	arg,\
	value\
);

SGE_OPENGL_INSTANTIATE_SET_TEXTURE_STAGE(
	sge::renderer::texture_stage_op::type,
	sge::renderer::texture_stage_op_value::type
)

SGE_OPENGL_INSTANTIATE_SET_TEXTURE_STAGE(
	sge::renderer::texture_stage_arg::type,
	sge::renderer::texture_stage_arg_value::type
)

#undef SGE_OPENGL_INSTANTIATE_SET_TEXTURE_STAGE

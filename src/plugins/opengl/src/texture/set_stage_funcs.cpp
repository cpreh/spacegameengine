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


#include <sge/opengl/texture/set_stage_funcs.hpp>
#include <sge/opengl/texture/convert/stage_arg.hpp>
#include <sge/opengl/texture/convert/stage_arg_value.hpp>
#include <sge/opengl/texture/convert/stage_op.hpp>
#include <sge/opengl/texture/convert/stage_op_value.hpp>
#include <sge/opengl/texture/funcs/env.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/sampler_stage_arg.hpp>
#include <sge/renderer/sampler_stage_arg_value.hpp>
#include <sge/renderer/sampler_stage_op.hpp>
#include <sge/renderer/sampler_stage_op_value.hpp>


template<
	typename Arg,
	typename Value
>
void
sge::opengl::texture::set_stage_funcs(
	context::object &_context,
	renderer::stage const _stage,
	Arg const _arg,
	Value const _value
)
{
	opengl::texture::funcs::set_active_level(
		_context,
		_stage
	);

	opengl::texture::funcs::env(
		GL_TEXTURE_ENV_MODE,
		GL_COMBINE
	);

	opengl::texture::funcs::env(
		texture::convert::stage_arg_op(
			_arg
		),
		texture::convert::stage_arg_op_value(
			_value
		)
	);
}

#define SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS(\
	arg,\
	value\
)\
template \
void \
sge::opengl::texture::set_stage_funcs(\
	sge::opengl::context::object &,\
	sge::renderer::stage,\
	arg,\
	value\
);

SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS(
	sge::renderer::sampler_stage_op::type,
	sge::renderer::sampler_stage_op_value::type
)

SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS(
	sge::renderer::sampler_stage_arg::type,
	sge::renderer::sampler_stage_arg_value::type
)

#undef SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS

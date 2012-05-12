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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/set_stage_funcs.hpp>
#include <sge/opengl/texture/convert/stage_arg.hpp>
#include <sge/opengl/texture/convert/stage_arg_value.hpp>
#include <sge/opengl/texture/convert/stage_op.hpp>
#include <sge/opengl/texture/convert/stage_op_value.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_arg.hpp>
#include <sge/renderer/texture/stage_arg_value.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <sge/renderer/texture/stage_op_value.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


template<
	typename Arg,
	typename Value
>
void
sge::opengl::texture::set_stage_funcs(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::texture::stage const _stage,
	Arg const _arg,
	Value const _value
)
{
	sge::opengl::texture::funcs::set_active_level(
		_system_context,
		_stage
	);

	sge::opengl::texture::funcs::env_int(
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_target
		>(
			GL_TEXTURE_ENV
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_arg
		>(
			GL_TEXTURE_ENV_MODE
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_int_value
		>(
			GL_COMBINE
		)
	);

	sge::opengl::texture::funcs::env_int(
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_target
		>(
			GL_TEXTURE_ENV
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_arg
		>(
			sge::opengl::texture::convert::stage_arg_op(
				_arg
			)
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::funcs::env_int_value
		>(
			sge::opengl::texture::convert::stage_arg_op_value(
				_value
			)
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
	sge::opengl::context::system::object &,\
	sge::renderer::texture::stage,\
	arg,\
	value\
);

SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS(
	sge::renderer::texture::stage_op::type,
	sge::renderer::texture::stage_op_value::type
)

SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS(
	sge::renderer::texture::stage_arg::type,
	sge::renderer::texture::stage_arg_value::type
)

#undef SGE_OPENGL_INSTANTIATE_TEXTURE_SET_STAGE_FUNCS

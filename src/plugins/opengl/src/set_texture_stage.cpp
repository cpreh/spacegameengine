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


#include "../set_texture_stage.hpp"
#include "../set_texture_level.hpp"
#include "../tex_envf_ext.hpp"
#include "../convert/texture_stage_op.hpp"
#include "../convert/texture_stage_op_value.hpp"
#include "../convert/texture_stage_arg.hpp"
#include "../convert/texture_stage_arg_value.hpp"
#include <sge/renderer/texture_stage_op.hpp>
#include <sge/renderer/texture_stage_op_value.hpp>
#include <sge/renderer/texture_stage_arg.hpp>
#include <sge/renderer/texture_stage_arg_value.hpp>

template<
	typename Arg,
	typename Value
>
void
sge::opengl::set_texture_stage(
	context::object &_context,
	renderer::stage_type const stage,
	Arg const arg,
	Value const value
)
{
	opengl::set_texture_level(
		_context,
		stage
	);

	opengl::tex_envf_ext(
		convert::texture_stage(
			arg
		),
		convert::texture_stage_value(
			value
		)
	);
}

#define SGE_OPENGL_INSTANTIATE_SET_TEXTURE_STAGE(\
	arg,\
	value\
)\
template \
void \
sge::opengl::set_texture_stage(\
	sge::opengl::context::object &,\
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

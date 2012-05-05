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
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/get_binding.hpp>
#include <sge/opengl/texture/get_stage_binding.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/convert/make_bind_type.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/optional_impl.hpp>


sge::opengl::texture::optional_id const
sge::opengl::texture::get_stage_binding(
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::funcs::set_active_level(
		_context,
		_stage
	);

	{
		sge::opengl::texture::optional_id const ret(
			sge::opengl::texture::get_binding(
				sge::opengl::texture::convert::make_bind_type(
					GL_TEXTURE_BINDING_1D
				)
			)
		);

		if(
			ret
		)
			return
				ret;
	}

	{
		sge::opengl::texture::optional_id const ret(
			sge::opengl::texture::get_binding(
				sge::opengl::texture::convert::make_bind_type(
					GL_TEXTURE_BINDING_2D
				)
			)
		);

		if(
			ret
		)
			return
				ret;
	}

	{
		sge::opengl::texture::cube_context const &cube_ctx(
			sge::opengl::context::use<
				sge::opengl::texture::cube_context
			>(
				_context
			)
		);

		if(
			cube_ctx.have_cube_texture()
		)
		{
			sge::opengl::texture::optional_id const ret(
				sge::opengl::texture::get_binding(
					cube_ctx.cube_texture_bind_type()
				)
			);

			if(
				ret
			)
				return
					ret;
		}
	}

	{
		sge::opengl::texture::volume_context const &volume_ctx(
			sge::opengl::context::use<
				sge::opengl::texture::volume_context
			>(
				_context
			)
		);

		if(
			volume_ctx.have_volume_texture()
		)
		{
			sge::opengl::texture::optional_id const ret(
				sge::opengl::texture::get_binding(
					volume_ctx.volume_texture_bind_type()
				)
			);

			if(
				ret
			)
				return
					ret;
		}
	}

	return
		sge::opengl::texture::optional_id();
}

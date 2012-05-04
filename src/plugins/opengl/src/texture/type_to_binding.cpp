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
#include <sge/opengl/texture/bind_type.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/type_to_binding.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/convert/make_bind_type.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::texture::bind_type const
sge::opengl::texture::type_to_binding(
	sge::opengl::context::object &_context,
	sge::opengl::texture::type const _type
)
{
	if(
		_type.get() == GL_TEXTURE_1D
	)
		return
			sge::opengl::texture::convert::make_bind_type(
				GL_TEXTURE_BINDING_1D
			);

	if(
		_type.get() == GL_TEXTURE_2D
	)
		return
			sge::opengl::texture::convert::make_bind_type(
				GL_TEXTURE_BINDING_2D
			);

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
			&&
			_type
			==
			cube_ctx.cube_texture_type()
		)
			return
				cube_ctx.cube_texture_bind_type();
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
			&&
			_type
			==
			volume_ctx.volume_texture_type()
		)
			return
				volume_ctx.volume_texture_bind_type();
	}

	FCPPT_ASSERT_UNREACHABLE;
}

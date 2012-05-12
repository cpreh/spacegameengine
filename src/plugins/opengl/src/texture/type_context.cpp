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
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/type_context.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/convert/make_bind_type.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::opengl::texture::type_context::type_map const
create_types(
	sge::opengl::texture::type_context::needs_before const &
);

}

sge::opengl::texture::type_context::type_context(
	sge::opengl::texture::type_context::needs_before const &_parameters
)
:
	sge::opengl::context::system::base(),
	types_(
		::create_types(
			_parameters
		)
	)
{
}

sge::opengl::texture::type_context::~type_context()
{
}

sge::opengl::texture::type_context::type_map const &
sge::opengl::texture::type_context::types() const
{
	return
		types_;
}

sge::opengl::context::system::id const
sge::opengl::texture::type_context::static_id(
	sge::opengl::context::system::make_id()
);

namespace
{

sge::opengl::texture::type_context::type_map const
create_types(
	sge::opengl::texture::type_context::needs_before const &_params
)
{
	sge::opengl::texture::type_context::type_map ret;

	ret.insert(
		sge::opengl::texture::type_context::type_map::value_type(
			sge::opengl::texture::convert::make_type(
				GL_TEXTURE_1D
			),
			sge::opengl::texture::convert::make_bind_type(
				GL_TEXTURE_BINDING_1D
			)
		)
	);

	ret.insert(
		sge::opengl::texture::type_context::type_map::value_type(
			sge::opengl::texture::convert::make_type(
				GL_TEXTURE_2D
			),
			sge::opengl::texture::convert::make_bind_type(
				GL_TEXTURE_BINDING_2D
			)
		)
	);

	{
		sge::opengl::texture::cube_context const &cube_ctx(
			*boost::fusion::at_c<
				0
			>(
				_params
			)
		);

		if(
			cube_ctx.have_cube_texture()
		)
			ret.insert(
				sge::opengl::texture::type_context::type_map::value_type(
					cube_ctx.cube_texture_type(),
					cube_ctx.cube_texture_bind_type()
				)
			);
	}

	{
		sge::opengl::texture::volume_context const &volume_ctx(
			*boost::fusion::at_c<
				1
			>(
				_params
			)
		);

		if(
			volume_ctx.have_volume_texture()
		)
			ret.insert(
				sge::opengl::texture::type_context::type_map::value_type(
					volume_ctx.volume_texture_type(),
					volume_ctx.volume_texture_bind_type()
				)
			);
	}

	return
		ret;
}

}

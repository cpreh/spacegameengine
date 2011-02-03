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


#include "basic_texture_surface.hpp"
#include "texfuncs/level_parameter.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

template<
	typename Base
>
sge::opengl::basic_texture_surface<Base>::basic_texture_surface(
	GLenum const _type,
	GLuint const _id,
	renderer::stage_type const _stage
)
:
	Base(),
	sge::opengl::texture_surface_base(
		_type,
		_id,
		_stage
	),
	dim_(
		static_cast<
			sge::renderer::size_type
		>(
			opengl::texfuncs::level_parameter(
				_type,
				_stage,
				GL_TEXTURE_WIDTH
			)
		),
		static_cast<
			sge::renderer::size_type
		>(
			opengl::texfuncs::level_parameter(
				_type,
				_stage,
				GL_TEXTURE_HEIGHT
			)
		)
	)
{
}

template<
	typename Base
>
sge::opengl::basic_texture_surface<Base>::~basic_texture_surface()
{
}

template<
	typename Base
>
typename sge::opengl::basic_texture_surface<Base>::dim_type const
sge::opengl::basic_texture_surface<Base>::dim() const
{
	return dim_;
}

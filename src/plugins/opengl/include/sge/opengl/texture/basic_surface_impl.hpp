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


#ifndef SGE_OPENGL_TEXTURE_BASIC_SURFACE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_SURFACE_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/basic_surface.hpp>
#include <sge/opengl/texture/surface_base.hpp>
#include <sge/opengl/texture/funcs/level_parameter.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

template<
	typename Base
>
sge::opengl::texture::basic_surface<Base>::basic_surface(
	texture::scoped_work_bind const &_binding,
	texture::type const _type,
	texture::id const _id,
	renderer::stage const _stage
)
:
	Base(),
	sge::opengl::texture::surface_base(
		_type,
		_id,
		_stage
	),
	dim_(
		static_cast<
			sge::renderer::size_type
		>(
			opengl::texture::funcs::level_parameter(
				_binding,
				_type,
				_stage,
				GL_TEXTURE_WIDTH
			)
		),
		static_cast<
			sge::renderer::size_type
		>(
			opengl::texture::funcs::level_parameter(
				_binding,
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
sge::opengl::texture::basic_surface<Base>::~basic_surface()
{
}

template<
	typename Base
>
typename sge::opengl::texture::basic_surface<Base>::dim const
sge::opengl::texture::basic_surface<Base>::size() const
{
	return dim_;
}

#endif

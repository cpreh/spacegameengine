/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../depth_stencil_texture.hpp"
#include <sge/renderer/resource_flags_none.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::opengl::depth_stencil_texture::depth_stencil_texture(
	dim_type const &_dim,
	renderer::depth_stencil_format::type const _format
)
:
	holder_(),
	dim_(_dim)
{
}

sge::opengl::depth_stencil_texture::~depth_stencil_texture()
{
}

GLuint
sge::opengl::depth_stencil_texture::id() const
{
	return holder_.id();
}

sge::opengl::depth_stencil_texture::dim_type const
sge::opengl::depth_stencil_texture::dim() const
{
	return dim_;
}

sge::renderer::resource_flags_field const
sge::opengl::depth_stencil_texture::flags() const
{
	return renderer::resource_flags::none;
}

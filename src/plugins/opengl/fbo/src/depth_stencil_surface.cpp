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


#include "../depth_stencil_surface.hpp"
#include <fcppt/math/dim/basic_impl.hpp>

sge::opengl::fbo::depth_stencil_surface::depth_stencil_surface(
	fbo::context const &_context,
	GLenum const _internal_format,
	sge::renderer::dim2 const &_dim
)
:
	render_buffer_(
		_context,
		_internal_format,
		_dim
	),
	dim_(_dim)
{
}

sge::opengl::fbo::depth_stencil_surface::~depth_stencil_surface()
{
}

sge::opengl::fbo::render_buffer const &
sge::opengl::fbo::depth_stencil_surface::render_buffer() const
{
	return render_buffer_;
}

sge::opengl::fbo::depth_stencil_surface::dim_type const
sge::opengl::fbo::depth_stencil_surface::dim() const
{
	return dim_;
}

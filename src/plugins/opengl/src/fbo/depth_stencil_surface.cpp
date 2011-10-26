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


#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/convert/depth_stencil_to_internal_format.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::opengl::fbo::depth_stencil_surface::depth_stencil_surface(
	fbo::context const &_context,
	renderer::depth_stencil_format::type const _format,
	dim const &_dim
)
:
	render_buffer_(
		_context,
		opengl::convert::depth_stencil_to_internal_format(
			_format
		),
		_dim
	),
	format_(_format),
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

sge::renderer::depth_stencil_format::type
sge::opengl::fbo::depth_stencil_surface::format() const
{
	return format_;
}

sge::opengl::fbo::depth_stencil_surface::dim const
sge::opengl::fbo::depth_stencil_surface::size() const
{
	return dim_;
}

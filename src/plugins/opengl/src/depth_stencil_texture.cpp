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


#include "../depth_stencil_texture.hpp"
#include "../common.hpp"
#include "../convert/depth_stencil_to_format.hpp"
#include "../convert/depth_stencil_to_format_type.hpp"
#include "../convert/depth_stencil_to_internal_format.hpp"
#include "../depth_stencil_texture_surface.hpp"
#include "../texfuncs/set.hpp"
#include "../texfuncs/set_filter.hpp"
#include <sge/renderer/filter/point.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>

// TODO: this should inherit from basic_texture as well!
sge::opengl::depth_stencil_texture::depth_stencil_texture(
	opengl::context::object &_context,
	dim_type const &_dim,
	renderer::depth_stencil_format::type const _format
)
:
	renderer::depth_stencil_texture(),
	opengl::texture_base(
		GL_TEXTURE_2D
	),
	holder_(),
	dim_(_dim),
	format_(
		_format
	)
{
	this->bind();

	sge::renderer::filter::texture const filter(
		sge::renderer::filter::point
	);

	texfuncs::set_filter(
		_context,
		type(),
		filter
	);

	texfuncs::set(
		_context,
		type(),
		convert::depth_stencil_to_format(
			_format
		),
		convert::depth_stencil_to_format_type(
			_format
		),
		convert::depth_stencil_to_internal_format(
			_format
		),
		filter,
		dim(),
		0
	);
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


sge::renderer::depth_stencil_surface_ptr const
sge::opengl::depth_stencil_texture::surface() const
{
	// TODO: clean this up!
	this->bind();

	return
		fcppt::make_shared_ptr<
			opengl::depth_stencil_texture_surface
		>(
			this->type(),
			this->id(),
			format_
		);
}

sge::renderer::resource_flags_field const
sge::opengl::depth_stencil_texture::flags() const
{
	return renderer::resource_flags::none;
}

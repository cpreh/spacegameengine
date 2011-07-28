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


#include "../depth_stencil.hpp"
#include "../depth_stencil_surface.hpp"
#include "../scoped_work_bind.hpp"
#include "../funcs/set_2d.hpp"
#include "../../common.hpp"
#include "../../convert/depth_stencil_to_format.hpp"
#include "../../convert/depth_stencil_to_format_type.hpp"
#include "../../convert/depth_stencil_to_internal_format.hpp"
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/stage.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>

// TODO: this should inherit from basic_texture as well!
sge::opengl::texture::depth_stencil::depth_stencil(
	opengl::context::object &_context,
	dim_type const &_dim,
	renderer::depth_stencil_format::type const _format
)
:
	renderer::texture::depth_stencil(),
	opengl::texture::base(
		opengl::texture::type(
			GL_TEXTURE_2D
		)
	),
	context_(_context),
	dim_(_dim),
	format_(
		_format
	)
{
	opengl::texture::scoped_work_bind const binding(
		_context,
		this->type(),
		this->id(),
		renderer::stage(
			0u
		)
	);

	texture::funcs::set_2d(
		binding,
		_context,
		this->type(),
		convert::depth_stencil_to_format(
			_format
		),
		convert::depth_stencil_to_format_type(
			_format
		),
		convert::depth_stencil_to_internal_format(
			_format
		),
		renderer::stage(
			0u
		),
		this->dim(),
		0
	);
}

sge::opengl::texture::depth_stencil::~depth_stencil()
{
}

sge::opengl::texture::depth_stencil::dim_type const
sge::opengl::texture::depth_stencil::dim() const
{
	return dim_;
}

sge::renderer::depth_stencil_surface_ptr const
sge::opengl::texture::depth_stencil::surface() const
{
	opengl::texture::scoped_work_bind const binding(
		context_,
		this->type(),
		this->id(),
		renderer::stage(
			0u
		)
	);

	return
		fcppt::make_shared_ptr<
			opengl::texture::depth_stencil_surface
		>(
			fcppt::cref(
				binding
			),
			this->type(),
			this->id(),
			format_
		);
}

sge::renderer::resource_flags_field const
sge::opengl::texture::depth_stencil::resource_flags() const
{
	return renderer::resource_flags::none;
}

sge::renderer::texture::capabilities_field const
sge::opengl::texture::depth_stencil::capabilities() const
{
	return
		renderer::texture::capabilities_field(
			renderer::texture::capabilities::render_target
		);
}

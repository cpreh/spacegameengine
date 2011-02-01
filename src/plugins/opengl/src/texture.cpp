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


#include "../texture.hpp"
#include "../basic_texture_impl.hpp"
#include "../common.hpp"
#include "../texture_surface.hpp"
#include "../texfuncs/get_parameter_int.hpp"
#include "../texfuncs/set.hpp"
#include "../texfuncs/set_rect.hpp"
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>

template class
sge::opengl::basic_texture<
	sge::renderer::texture
>;

namespace
{

GLenum const texture_type = GL_TEXTURE_2D;

}

sge::opengl::texture::texture(
	context::object &_context,
	dim_type const &_dim,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags,
	optional_type const &_type
)
:
	detail::texture_base(
		_context,
		_filter,
		_flags,
		_type
		?
			*_type
		:
			texture_type,
		_format,
		_dim
	)
{
	texfuncs::set(
		_context,
		type(),
		format(),
		format_type(),
		internal_format(),
		filter(),
		dim(),
		0
	);
}

sge::opengl::texture::~texture()
{
}

void
sge::opengl::texture::set_area(
	lock_area const &_area,
	pointer const _dest
) const
{
	texfuncs::set_rect(
		context(),
		type(),
		format(),
		format_type(),
		dim(),
		_area,
		_dest
	);
}

sge::renderer::color_surface_ptr const
sge::opengl::texture::surface(
	renderer::stage_type const _stage
)
{
	// important for the construct of texture_surface to work!
	this->bind();

	return
		fcppt::make_shared_ptr<
			opengl::texture_surface
		>(
			this->id(),
			this->type(),
			_stage
		);
}

sge::renderer::stage_type
sge::opengl::texture::stages() const
{
	this->bind();

	return
		renderer::stage_type(
			static_cast<
				renderer::stage_type::value_type
			>(
				texfuncs::get_parameter_int(
					this->type(),
					GL_TEXTURE_BASE_LEVEL
				)
			)
		);
}

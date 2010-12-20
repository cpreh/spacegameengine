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


#include "../texture.hpp"
#include "../basic_texture_impl.hpp"
#include "../common.hpp"
#include "../texfuncs/set.hpp"
#include "../texfuncs/set_rect.hpp"
#include <sge/renderer/texture.hpp>
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

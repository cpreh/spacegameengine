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


#include "../volume_texture.hpp"
#include "../basic_texture_impl.hpp"
#include "../volume_texture_context.hpp"
#include "../context/use.hpp"
#include "../texfuncs/set_3d.hpp"
#include "../texfuncs/set_rect_3d.hpp"
#include <sge/renderer/volume_texture.hpp>

template class
sge::opengl::basic_texture<
	sge::renderer::volume_texture
>;

sge::opengl::volume_texture::volume_texture(
	opengl::context::object &_context,
	dim_type const &_dim,
	sge::image::color::format::type const _format,
	sge::renderer::filter::texture const &_filter,
	sge::renderer::resource_flags_field const &_flags
)
:
	detail::volume_texture_base(
		_context,
		_filter,
		_flags,
		opengl::context::use<
			opengl::volume_texture_context
		>(
			_context
		).volume_texture_type(),
		_format,
		_dim
	)
{
	texfuncs::set_3d(
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

sge::opengl::volume_texture::~volume_texture()
{
}

void
sge::opengl::volume_texture::set_area(
	lock_area const &_area,
	pointer const _dest
) const
{
	texfuncs::set_rect_3d(
		context(),
		type(),
		format(),
		format_type(),
		dim(),
		_area,
		_dest
	);
}

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


#include "../volume.hpp"
#include "../basic_impl.hpp"
#include "../scoped_work_bind.hpp"
#include "../volume_context.hpp"
#include "../funcs/set_3d.hpp"
#include "../funcs/set_rect_3d.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/volume_texture.hpp>

template class
sge::opengl::texture::basic<
	sge::renderer::volume_texture
>;

sge::opengl::texture::volume::volume(
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
			opengl::texture::volume_context
		>(
			_context
		).volume_texture_type(),
		_format,
		_dim
	)
{
	opengl::texture::scoped_work_bind const binding(
		_context,
		*this,
		renderer::stage_type(0u)
	);

	texture::funcs::set_3d(
		binding,
		_context,
		this->type(),
		this->format(),
		this->format_type(),
		this->internal_format(),
		this->filter(),
		this->dim(),
		0
	);
}

sge::opengl::texture::volume::~volume()
{
}

void
sge::opengl::texture::volume::set_area(
	opengl::texture::scoped_work_bind const &_binding,
	lock_area const &_area,
	pointer const _dest
) const
{
	texture::funcs::set_rect_3d(
		_binding,
		this->context(),
		this->type(),
		this->format(),
		this->format_type(),
		this->dim(),
		_area,
		_dest
	);
}

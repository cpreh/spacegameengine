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
#include "../volume_types.hpp"
#include "../basic_impl.hpp"
#include "../scoped_work_bind.hpp"
#include "../volume_context.hpp"
#include "../funcs/set_3d.hpp"
#include "../funcs/set_box.hpp"
#include "../../context/use.hpp"
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters.hpp>

template class
sge::opengl::texture::basic<
	sge::opengl::texture::volume_types
>;

sge::opengl::texture::volume::volume(
	opengl::context::object &_context,
	renderer::texture::volume_parameters const &_param
)
:
	texture::volume_basic(
		_context,
		opengl::context::use<
			opengl::texture::volume_context
		>(
			_context
		).volume_texture_type(),
		_param
	)
{
	opengl::texture::scoped_work_bind const binding(
		_context,
		this->type(),
		this->id(),
		renderer::stage(0u)
	);

	texture::funcs::set_3d(
		binding,
		_context,
		this->type(),
		this->format(),
		this->format_type(),
		this->internal_format(),
		renderer::stage(0u),
		this->size(),
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
	texture::funcs::set_box(
		_binding,
		this->context(),
		this->type(),
		this->format(),
		this->format_type(),
		renderer::stage(0u),
		this->size(),
		_area,
		_dest
	);
}

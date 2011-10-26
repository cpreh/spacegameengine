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


#include <sge/opengl/texture/volume.hpp>
#include <sge/opengl/texture/volume_types.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/context/use.hpp>
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
}

sge::opengl::texture::volume::~volume()
{
}

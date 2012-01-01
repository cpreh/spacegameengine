/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/check_and_set.hpp>
#include <sge/opengl/texture/volume.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/volume_types.hpp>
#include <sge/opengl/texture/address_mode/default.hpp>
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
	),
	address_mode_u_(
		sge::renderer::texture::address_mode::repeat
	)
{
}

sge::opengl::texture::volume::~volume()
{
}

bool
sge::opengl::texture::volume::update_address_mode_u(
	renderer::texture::address_mode_u const _address_mode
) const
{
	return
		opengl::texture::check_and_set(
			address_mode_u_,
			_address_mode
		);
}

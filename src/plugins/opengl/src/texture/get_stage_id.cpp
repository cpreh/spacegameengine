/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/opengl/texture/get_stage_id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/renderer/texture/stage.hpp>


sge::opengl::texture::optional_id const
sge::opengl::texture::get_stage_id(
	sge::opengl::context::device::object &_device_context,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::bind_context const &bind_context(
		sge::opengl::context::use<
			sge::opengl::texture::bind_context
		>(
			_device_context
		)
	);

	sge::opengl::texture::const_optional_base_ref const texture(
		bind_context.stage(
			_stage
		)
	);

	return
		texture
		?
			sge::opengl::texture::optional_id(
				texture->id()
			)
		:
			sge::opengl::texture::optional_id()
		;
}

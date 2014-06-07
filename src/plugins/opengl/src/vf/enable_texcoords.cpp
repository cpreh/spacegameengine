/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/enable_client_state.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/opengl/vf/enable_texcoords.hpp>
#include <sge/renderer/texture/stage.hpp>


void
sge::opengl::vf::enable_texcoords(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::texture::stage const _index
)
{
	opengl::texture::funcs::set_client_level(
		_system_context,
		_index
	);

	sge::opengl::enable_client_state(
		GL_TEXTURE_COORD_ARRAY
	);
}

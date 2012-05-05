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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/bind_level.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/funcs/bind.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>


void
sge::opengl::texture::bind_level(
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const _stage,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::optional_id const &_id
)
{
	sge::opengl::texture::funcs::set_active_level(
		_context,
		_stage
	);

	sge::opengl::texture::funcs::bind(
		_type,
		_id
	);
}

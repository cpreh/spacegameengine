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
#include <sge/opengl/texture/get_binding.hpp>
#include <sge/opengl/texture/get_type_binding.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/type_to_binding.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/optional_impl.hpp>


sge::opengl::texture::optional_id const
sge::opengl::texture::get_type_binding(
	sge::opengl::context::object &_context,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::funcs::set_active_level(
		_context,
		_stage
	);

	return
		sge::opengl::texture::get_binding(
			sge::opengl::texture::type_to_binding(
				_context,
				_type
			)
		);
}

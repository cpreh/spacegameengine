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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/get_binding.hpp>
#include <sge/opengl/texture/get_stage_type.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/type_context.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/optional_impl.hpp>


sge::opengl::texture::optional_type const
sge::opengl::texture::get_stage_type(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::funcs::set_active_level(
		_system_context,
		_stage
	);

	sge::opengl::texture::type_context::type_map const &map(
		sge::opengl::context::use<
			sge::opengl::texture::type_context
		>(
			_system_context
		).types()
	);

	for(
		sge::opengl::texture::type_context::type_map::left_const_iterator it(
			map.left.begin()
		);
		it != map.left.end();
		++it
	)
	{
		if(
			sge::opengl::texture::get_binding(
				it->second
			)
		)
			return
				sge::opengl::texture::optional_type(
					it->first
				);
	}

	return
		sge::opengl::texture::optional_type();
}

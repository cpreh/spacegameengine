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


#include <sge/opengl/cg/texture/set_samplers.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/get_type_binding.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::texture::stage const
sge::opengl::cg::texture::set_samplers(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::context::object &_context,
	sge::opengl::texture::base const &_texture,
	sge::renderer::caps::texture_stages const _max_stages
)
{
	for(
		sge::renderer::texture::stage stage(
			0u
		);
		stage.get() < _max_stages.get();
		++stage
	)
	{
		sge::opengl::texture::optional_id const id(
			sge::opengl::texture::get_type_binding(
				_context,
				_texture.type(),
				stage
			)
		);

		if(
			id
			&&
			*id
			==
			_texture.id()
		)
		{
			sge::opengl::texture::set_samplers(
				_binding,
				_context,
				_texture.type(),
				stage
			);

			return stage;
		}
	}

	FCPPT_ASSERT_UNREACHABLE;
}

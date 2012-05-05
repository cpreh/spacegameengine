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


#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_level.hpp>
#include <sge/opengl/texture/get_stage_type.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/address_mode/set.hpp>
#include <sge/opengl/texture/filter/set.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/optional_impl.hpp>


void
sge::opengl::texture::activate(
	sge::opengl::context::object &_context,
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::funcs::set_active_level(
		_context,
		_stage
	);

	if(
		!_texture
	)
	{
		sge::opengl::texture::optional_type const old_type(
			sge::opengl::texture::get_stage_type(
				_context,
				_stage
			)
		);

		if(
			old_type
		)
		{
			sge::opengl::disable(
				old_type->get()
			);

			sge::opengl::texture::bind_level(
				_context,
				_stage,
				*old_type,
				sge::opengl::texture::optional_id()
			);

		}
		return;
	}

	sge::opengl::texture::base const &base(
		dynamic_cast<
			sge::opengl::texture::base const &
		>(
			*_texture
		)
	);

	sge::opengl::enable(
		base.type().get()
	);

	sge::opengl::texture::bind_level(
		_context,
		_stage,
		base.type(),
		sge::opengl::texture::optional_id(
			base.id()
		)
	);

	sge::opengl::texture::render_binding const binding;

	sge::opengl::texture::filter::set(
		_context,
		binding,
		base.type(),
		_stage
	);

	sge::opengl::texture::address_mode::set(
		_context,
		binding,
		base.type(),
		_stage
	);
}

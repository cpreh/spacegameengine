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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/address_mode/set.hpp>
#include <sge/opengl/texture/filter/set.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base.hpp>
#include <sge/renderer/texture/stage.hpp>


void
sge::opengl::texture::activate(
	opengl::context::object &_context,
	sge::renderer::texture::const_optional_base const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	opengl::texture::bind_context &context(
		context::use<
			opengl::texture::bind_context
		>(
			_context
		)
	);

	// TODO: Should we activate this code?
#if 0
	if(
		dynamic_cast<
			opengl::texture::base const *
		>(
			_texture
		)
		==
		context.render_texture(
			_stage
		)
	)
		return;
#endif
	if(
		!_texture
	)
	{
		context.unbind_for_rendering(
			_context,
			_stage
		);

		return;
	}

	opengl::texture::base const &texture_base(
		dynamic_cast<
			opengl::texture::base const &
		>(
			*_texture
		)
	);

	context.bind_for_rendering(
		_context,
		texture_base,
		_stage
	);

	opengl::texture::render_binding const binding(
		_context,
		_stage
	);

	sge::opengl::texture::filter::set(
		_context,
		binding,
		texture_base,
		_stage
	);

	sge::opengl::texture::address_mode::set(
		_context,
		binding,
		texture_base,
		_stage
	);
}

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


#include "../set_texture.hpp"
#include "../enable.hpp"
#include "../disable.hpp"
#include "../set_texture_level.hpp"
#include "../texture_base.hpp"
#include "../texture_context.hpp"
#include "../context/use.hpp"
#include <sge/renderer/texture_base.hpp>

void
sge::opengl::set_texture(
	opengl::context::object &_context,
	sge::renderer::const_texture_base_ptr const _texture,
	sge::renderer::stage_type const _stage
)
{
	opengl::set_texture_level(
		_context,
		_stage
	);

	opengl::texture_context &context(
		context::use<
			texture_context
		>(
			_context
		)
	);

	GLenum const last_type(
		context.last_type(
			_stage
		)
	);

	if(
		!_texture
	)
	{
		if(
			last_type
			!= texture_context::invalid_type
		)
		{
			opengl::disable(
				last_type
			);

			context.last_type(
				texture_context::invalid_type,
				_stage
			);
		}

		return;
	}
	
	opengl::texture_base const &base(
		dynamic_cast<
			opengl::texture_base const &
		>(
			*_texture
		)
	);

	if(
		last_type
		!= base.type()
	)
	{
		if(
			last_type
			!= texture_context::invalid_type
		)
			opengl::disable(
				last_type
			);

		opengl::enable(
			base.type()
		);

		context.last_type(
			base.type(),
			_stage
		);
	}

	base.bind();
}

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


#include "../update_filter.hpp"
#include "../bind_context.hpp"
#include "../filter_context.hpp"
#include "../funcs/set_filter.hpp"
#include "../../context/use.hpp"

void
sge::opengl::texture::update_filter(
	opengl::context::object &_context,
	sge::renderer::stage const _stage,
	sge::renderer::texture::filter::object const &_filter
)
{
	if(
		!opengl::context::use<
			opengl::texture::filter_context
		>(
			_context
		).set(
			_stage,
			_filter
		)
	)
		return;

	opengl::texture::base const *const bound_texture(
		opengl::context::use<
			opengl::texture::bind_context
		>(
			_context
		).render_texture(
			_stage
		)
	);

	if(
		!bound_texture
	)
		return;

	opengl::texture::funcs::set_filter(
		_context,
		*bound_texture,
		_stage,
		_filter
	);
}

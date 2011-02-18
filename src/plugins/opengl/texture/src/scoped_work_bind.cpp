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


#include "../scoped_work_bind.hpp"
#include "../bind_context.hpp"
#include "../../context/use.hpp"

sge::opengl::texture::scoped_work_bind::scoped_work_bind(
	opengl::context::object &_context,
	opengl::texture::type const _type,
	opengl::texture::id const _id,
	renderer::stage_type const _stage
)
:
	context_(
		_context
	),
	bind_context_(
		opengl::context::use<
			texture::bind_context
		>(
			_context
		)
	),
	stage_(
		_stage
	)
{
	bind_context_.bind_for_work(
		_context,
		_type,
		_id,
		_stage
	);
}

sge::opengl::texture::scoped_work_bind::~scoped_work_bind()
{
	bind_context_.unbind_for_work(
		context_,
		stage_
	);
}

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


#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/last_context.hpp>
#include <sge/opengl/fbo/object.hpp>
#include <sge/opengl/fbo/temporary_bind.hpp>


sge::opengl::fbo::temporary_bind::temporary_bind(
	sge::opengl::fbo::context &_context,
	sge::opengl::fbo::last_context &_last_context,
	sge::opengl::fbo::object const &_object
)
:
	context_(
		_context
	),
	last_context_(
		_last_context
	),
	last_buffer_(
		last_context_.last_buffer()
	)
{
	_object.bind();
}

sge::opengl::fbo::temporary_bind::~temporary_bind()
{
	sge::opengl::fbo::bind(
		context_,
		last_buffer_
	);

	last_context_.last_buffer(
		last_buffer_
	);
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/fbo/attach_render_buffer.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/opengl/fbo/render_buffer_binding.hpp>


sge::opengl::fbo::render_buffer_binding::render_buffer_binding(
	sge::opengl::fbo::context const &_context,
	sge::opengl::fbo::render_buffer const &_render_buffer,
	sge::opengl::fbo::attachment_type const _what
)
:
	context_(
		_context
	),
	what_(
		_what
	)
{
	sge::opengl::fbo::attach_render_buffer(
		_context,
		_what,
		_render_buffer.id()
	);
}

sge::opengl::fbo::render_buffer_binding::~render_buffer_binding()
{
	sge::opengl::fbo::attach_render_buffer(
		context_,
		what_,
		0
	);
}

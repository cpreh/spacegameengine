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


#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/delete_render_buffer.hpp>
#include <sge/opengl/fbo/gen_render_buffer.hpp>
#include <sge/opengl/fbo/render_buffer_holder.hpp>


sge::opengl::fbo::render_buffer_holder::render_buffer_holder(
	sge::opengl::fbo::config const &_context
)
:
	context_(
		_context
	),
	id_(
		sge::opengl::fbo::gen_render_buffer(
			context_
		)
	)
{
}

sge::opengl::fbo::render_buffer_holder::~render_buffer_holder()
{
	sge::opengl::fbo::delete_render_buffer(
		context_,
		id_
	);
}

GLuint
sge::opengl::fbo::render_buffer_holder::id() const
{
	return
		id_;
}
